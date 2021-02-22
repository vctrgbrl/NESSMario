#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "GameProps.h"

class Platformer : public olc::PixelGameEngine
{
private:
    LevelMap* m_Level;

    std::string SpriteIDArray;
    unsigned char* FlagsArray;
public:
    bool OnUserCreate() override {

        // Define Game Properties
        GameProps::Game = this;
        GameProps::Resolution = { ScreenWidth(), ScreenHeight() };
        GameProps::TileSize = 16;
        GameProps::nVisibleTiles = { (float) (ScreenWidth()/16), (float)(ScreenHeight()/16) };
        SetPixelMode(olc::Pixel::MASK);

        // Creates Level

        /// 
        /// . = Air/Nothing
        /// ? = Mistery Box
        /// B = Brick
        /// # = Ground block
        /// [] = upside of the pipes
        /// {} = bottom of pipe
        /// P  = indicates a pipe that you can go in
        /// H  = Hard Block
        /// E  = indicates an exit of a pipe tunel
        /// |  = flag pole
        /// o  = flag circle
        /// D  = death block
        /// <returns></returns>

        FlagsArray = new unsigned char[210*22];
        SpriteIDArray += "..................................................................................................................................................................................................................";
        SpriteIDArray += "..................................................................................................................................................................................................................";
        SpriteIDArray += "......................................................................................................................................................................................................o...........";	// 0
        SpriteIDArray += "......................................................................................................................................................................................................|...........";	// 1
        SpriteIDArray += "......................................................................................................................................................................................................|...........";	// 2
        SpriteIDArray += "................................................................................BBBBBBBB...BBB?..............?...........BBB....B??B........................................................HH........|...........";	// 3
        SpriteIDArray += "......................?....................................................................................................................................................................HHH........|...........";	// 4
        SpriteIDArray += "..........................................................................................................................................................................................HHHH........|...........";	// 5
        SpriteIDArray += ".........................................................PP......I.......................................................................................................................HHHHH........|...........";	// 6
        SpriteIDArray += ".........BBBBB..?...B?B?B.....................[].........[]..................B?B..............B.....BB....?..?..?.....B..........BB......H..H..........HH..H............BB?B............HHHHHH........|...........";	// 7
        SpriteIDArray += "......................................[]......{}.........{}.............................................................................HH..HH........HHH..HH......EE..................HHHHHHH........|...........";	// 8
        SpriteIDArray += "............................[]........{}......{}.........{}............................................................................HHH..HHH......HHHH..HHH.....[]..............[].HHHHHHHH........|...........";	// 9
        SpriteIDArray += ".........................G..{}........{}......{}.........{}...........................................................................HHHH..HHHH....HHHHH..HHHH....{}..............{}HHHHHHHHH........H...........";	// 10
        SpriteIDArray += "#####################################################################..###############...################################################################DD#######################################################";	// 11
        SpriteIDArray += "#####################################################################DD###############DDD################################################################..#######################################################";	// 12
        SpriteIDArray += "..................................................................................................................................................................................................................";	// 13
        SpriteIDArray += "..................................................................................................................................................................................................................";	// 14
        SpriteIDArray += "..................................................................................................................................................................................................................";	// 15
        SpriteIDArray += "..................................................................................................................................................................................................................";	// 16
        SpriteIDArray += "..................................................................................................................................................................................................................";	// 17
        SpriteIDArray += "..................................................................................................................................................................................................................";	// 18
        SpriteIDArray += "..................................................................................................................................................................................................................";	// 19

        // 0x80 Solid
        // 0x40 Death
        // 0x20 Dynamic
        // 0x10
        GameProps::dynCol = new DynamicsCollection();
        for (int y = 0; y < 22; y++)
        {
            for (int x = 0; x < 210; x++)
            {
                switch (SpriteIDArray[y*210 + x])
                {
                case '.':
                    FlagsArray[y * 210 + x] = 0x00;
                    break;
                case '#':
                case 'H':
                case '[':
                case ']':
                case '{':
                case '}':
                    FlagsArray[y * 210 + x] = 0x80;
                    break;
                case 'D':
                    FlagsArray[y * 210 + x] = 0x40;
                    break;
                case 'G':
                    FlagsArray[y * 210 + x] = 0x20;
                    GameProps::dynCol->dynamicsVector.push_back(new Goomba(olc::vf2d({ (float)x, (float)y }), olc::vf2d(1,0)));
                    break;
                case '?':
                    FlagsArray[y * 210 + x] = 0x20;
                    GameProps::dynCol->dynamicsVector.push_back(new MisteryBlock(olc::vf2d({ (float)x, (float)y })) );
                    break;
                case 'B':
                    // DynamicsMap.Add(new DynamicBlock(spriteID, position));
                    FlagsArray[y * 210 + x] = 0x20;
                    GameProps::dynCol->dynamicsVector.push_back(new BrickBlock(olc::vf2d({ (float)x, (float)y })));
                    break;
                default:
                    FlagsArray[y * 210 + x] = 0x00;
                    break;
                }
            }
        }
        m_Level = new LevelMap(210, 22, SpriteIDArray, FlagsArray);
        GameProps::Level = m_Level;
        GameProps::CameraPos.y = 7;

        GameProps::m_Player = new Player({3,8}, 100.f, 30.f, 13.f, 20.f);

        delete[] FlagsArray;
        return true;
    }
    bool OnUserUpdate(float deltaTime) override {
        Clear(olc::Pixel(0xFFecbb93));
        GameProps::deltaTime = deltaTime;

        // Player Input
        GameProps::m_Player->isWalking = false;
        GameProps::MousePos = { (float)GetMouseX() / GameProps::TileSize, (float)GetMouseY() / GameProps::TileSize };
        if (GameProps::m_Player->AllowInput)
        {
            if (GetKey(olc::Key::A).bHeld) { GameProps::m_Player->Move(DynamicCreature::MovDirection::LEFT); }
            if (GetKey(olc::Key::D).bHeld) { GameProps::m_Player->Move(DynamicCreature::MovDirection::RIGHT); }
            if (GetKey(olc::Key::SPACE).bPressed) { GameProps::m_Player->Move(DynamicCreature::MovDirection::JUMP); }
            if (GetKey(olc::Key::SPACE).bHeld) { GameProps::m_Player->Move(DynamicCreature::MovDirection::FLOAT); }
        }

        GameProps::m_Player->Update();
        for (int i = 0; i < GameProps::dynCol->dynamicsVector.size(); i++)
        {
            GameProps::dynCol->dynamicsVector[i]->Update();
        }
     
        GameProps::CameraPos.x = GameProps::m_Player->WorldPos.x;
        if (GameProps::CameraPos.x <= GameProps::nVisibleTiles.x/2) { GameProps::CameraPos.x = GameProps::nVisibleTiles.x/2; }
        if (GameProps::CameraPos.x >= GameProps::Level->GetWidth() - GameProps::nVisibleTiles.x / 2) { GameProps::CameraPos.x = GameProps::Level->GetWidth() - GameProps::nVisibleTiles.x / 2; }

        m_Level->DrawSelf();
        for (int i = 0; i < GameProps::dynCol->dynamicsVector.size(); i++)
        {
            GameProps::dynCol->dynamicsVector[i]->DrawSelf();
        }
        GameProps::m_Player->DrawSelf();
        return true;
    }
    bool OnUserDestroy() override {
        delete m_Level;
        delete GameProps::m_Player;
        return true;
    }
};

int main() {
    Platformer game;
    if (game.Construct(256, 240, 2,2))
    {
        game.Start();
    }
}