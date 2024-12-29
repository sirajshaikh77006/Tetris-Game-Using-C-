#include "game.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
}

Block Game::GetRandomBlock(){
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    return block;
    
}


std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}


void Game::Draw(){
    grid.Draw();
    currentBlock.Draw(11,11);
    // nextBlock.Draw(270,270);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255,290);
        break;
    case 4:
        nextBlock.Draw(255,280);
    
    default:
        nextBlock.Draw(270,270);
        break;
    }
}

void Game::HandleInput(){
    int keyPressed = GetKeyPressed();// method of raylib to detect the key press
    if (gameOver && keyPressed !=0)
    {
        gameOver = false;
        Reset();
    }
    
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0,1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}


void Game::MoveBlockLeft(){
    if (!gameOver)
    {
        currentBlock.Move(0,-1);
        if(IsBlockOutside() || BlockFits() == false){
        currentBlock.Move(0,1);
        } 
    }
    
    
}

void Game::MoveBlockRight(){
    if(!gameOver){
         currentBlock.Move(0,1);
        if(IsBlockOutside() || BlockFits() == false){
        currentBlock.Move(0,-1);
        }
    }
   
}

void Game::MoveBlockDown(){
    if(!gameOver){
        currentBlock.Move(1,0);
        if(IsBlockOutside() || BlockFits() == false){
        currentBlock.Move(-1,0);
        LockBlock();
        }
    }
    
}

bool Game::IsBlockOutside(){
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item: tiles){
        if(grid.IsCellOutside(item.row, item.column)){
            return true;
        }
    }
    return false;
}

void Game::RotateBlock(){
    if(!gameOver){
        currentBlock.Rotate();
        if(IsBlockOutside() || BlockFits() == false){
        currentBlock.UndoRotation();
        }
    }
    
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles){
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits() == false){
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
}

void Game::Reset(){
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int LinesCleared, int moveDownPoints){
    switch (LinesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
    case 3:
        score +=  500;
    default:
        break;
    }

    score += moveDownPoints;
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item: tiles){
        if(grid.IsCellEmpty(item.row, item.column) == false){
            return false;
        }
    }
    return true;
}