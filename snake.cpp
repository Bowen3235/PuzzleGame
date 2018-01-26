//
//  snake.cpp
//  final project_demo
//
//  Created by nettoycrick on 2018/1/5.
//  Copyright © 2018年 nettoycrick. All rights reserved.
//

#include "snake.hpp"

void snake::append(){
    
}
myarray::myarray(){
    array=NULL;
    array=new int[num+1];
}
void myarray::append(int newmem){
    int* temp=NULL;
    num+=1;
    temp=new int[num];
    for(int i=0;i<num-1;i++){
        temp[i]=this->array[i];
    }
    temp[num-1]=newmem;
    myarray();
    this->array=new int[num];
    for(int i=0;i<num;i++){
        this->array[i]=temp[i];
    }
    delete temp;
}
