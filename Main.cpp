#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;
using namespace sf;
using namespace Style;

struct Node
{
	int TreeID;
	int Xpos;
	int Ypos;
};

struct Edge
{
	sf::Vector2i vertexOne;
	sf::Vector2i vertexTwo;
	int weight;
};


int main() {

	//Create the Window
	RenderWindow mainWindow(VideoMode(700, 600), "Kruskal's Minimum Spanning Tree",Close);
	mainWindow.setFramerateLimit(30);

	//Disable Key Repetition to enable button pressed events
	mainWindow.setKeyRepeatEnabled(false);

	//Every vertex is assigned a Unique Tree ID in the Beginning
	int treeID = 0;

	//Var to store mouse position
	Vector2i localPosition;

	//Visual vertex
	CircleShape visNode;
	visNode.setRadius(5);
	visNode.setFillColor(sf::Color::Blue);
	visNode.setOrigin(6, 6);
	visNode.setScale(3, 3);

	//Visual edge
	RectangleShape primitiveLine;

	//Storage vectors
	vector<Vector2i> pointVector;
	vector<VertexArray> lineVector;
	vector<VertexArray> linkedVector;

	//Temporary active vertex storage vector
	vector<sf::Vector2i> activeTemp;

	//Node vector for mathematical calculation
	vector<Node> nodeVect;
	vector<Edge> edgeVect;

	//Bool for starting the calculations
	bool calcStarted = false;


	while (mainWindow.isOpen())
	{
		mainWindow.display();
	}
}