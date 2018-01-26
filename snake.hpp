//
//  snake.hpp
//  final project_demo
//
//  Created by nettoycrick on 2018/1/5.
//  Copyright © 2018年 nettoycrick. All rights reserved.
//

#ifndef snake_hpp
#define snake_hpp
#include "backgroundfunction.hpp"

#include <stdio.h>
struct myarray{
    int num=1;
    int* array=NULL;
    myarray();
    void append(int newmem);
};

class snake{
public:
    snake();
    void append();
    void render();
    void changestate();
    
private:
    myarray pos;
    myarray velo;
    
    
};




#endif /* snake_hpp */
