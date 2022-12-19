#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;
using namespace sf;

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
	RenderWindow mainWindow(VideoMode(700, 600), "Kruskal's Minimum Spanning Tree", Style::Close);
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
	vector<Vector2i> pointVector;            //vertices
	vector<VertexArray> lineVector;         //edges
	vector<VertexArray> linkedVector;      //edges for MST

	//Temporary active vertex storage vector
	vector<Vector2i> activeTemp;

	//Vectors for mathematical calculation
	vector<Node> nodeVect;
	vector<Edge> edgeVect;

	//Bool for starting the calculations
	bool calcStarted = false;

	while (mainWindow.isOpen())
	{
		//Get mouse position
		localPosition = Mouse::getPosition(mainWindow);

		Event event;
		while (mainWindow.pollEvent(event))
		{
			//Close window when x button is pressed
			if (event.type == Event::Closed)
				mainWindow.close();

			//Check if mose is pressed and calculations haven't started
			if (event.type == Event::MouseButtonPressed)
			{
				if (!calcStarted)
				{
					if (event.key.code == Mouse::Left)
					{
						bool validPos = true;

						for (int i = 0; i < pointVector.size(); i++)
						{
							/*If two points are two closeand may intersect then it's not a valid position and
							the edge is not added */

							if (sqrt(pow((localPosition.x - pointVector[i].x), 2) + pow((localPosition.y - pointVector[i].y), 2)) < 100)
							{
								validPos = false;
							}
						}

						if (validPos)
						{
							//Add vertex (node) to main vector
							pointVector.push_back(localPosition);

							//Update the Node Vector
							Node newNode;
							newNode.TreeID = treeID;
							treeID++;

							newNode.Xpos = localPosition.x;
							newNode.Ypos = localPosition.y;

							nodeVect.push_back(newNode);

							cout << "- Node Added -" << endl;
							cout << "X - Position: " << newNode.Xpos << endl;
							cout << "Y - Position: " << newNode.Ypos << endl;
							cout << "TreeID: " << treeID << endl;
							cout << endl << endl;
						}
					}
				}

				//Clear previous frames
				mainWindow.clear(Color::Black);

				//Draw all the given edges and vertices
				for (int i = 0; i < lineVector.size(); i++)
				{
					mainWindow.draw(lineVector[i]);
				}

				for (int i = 0; i < linkedVector.size(); i++)
				{
					mainWindow.draw(linkedVector[i]);
				}

				for (int i = 0; i < pointVector.size(); i++)
				{
					visNode.setPosition(pointVector[i].x, pointVector[i].y);
					mainWindow.draw(visNode);
				}


				mainWindow.display();
			}
		}
	}
	return 0;
}