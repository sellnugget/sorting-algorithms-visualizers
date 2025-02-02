
// SFMLSETUP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SFML/Audio.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Sorter.h"
#include <thread>
#include <windows.h> 

int main()
{

 
    int arraySize = 300;
    Sorter<int> sorter;
    sorter.LagSkips = 10;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

    std::vector<int> array;

    for (int i = 0; i < arraySize; i++) {
        sorter.array.push_back(i);
    }
    for (int i = 0; i < arraySize; i++) {
        int indexA = rand() % arraySize;
        int indexB = rand() % arraySize;
        int ValueA = sorter.array[indexA];
        sorter.array[indexA] = sorter.array[indexB];
        sorter.array[indexB] = ValueA;
    }

    std::function<bool(int, int)> fn = [](int a, int b) {return a > b; };
    sorter.SortThread(fn);
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " \n";
    }

    sf::RectangleShape* shape = new sf::RectangleShape[arraySize];
    
    


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
       
        window.clear();


        for (int i = 0; i < arraySize; i++) {
            if (sorter.currentSelection == i) {
                shape[i].setFillColor(sf::Color::Green);
            }
            else {

                shape[i].setFillColor(sf::Color((1-(sorter.array[i] / (float)arraySize)) * 255, 0,255));
            }
            shape[i].setPosition(sf::Vector2f((window.getSize().x / (float)arraySize) * i, window.getSize().y - (window.getSize().y / (float)arraySize) * sorter.array[i]));
            shape[i].setSize(sf::Vector2f(window.getSize().x / (float)arraySize, (window.getSize().y / (float)arraySize) * sorter.array[i]));
            window.draw(shape[i]);
        }
       
        // put game logic here and rendering code here


        window.display();
    }
}