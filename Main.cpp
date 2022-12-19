#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;
using namespace sf;

//Defining data structures for vertices and edges

struct Node 
{
	int TreeID;
	int Xpos;
	int Ypos;
};

struct Edge
{
	Vector2i vertexOne;
	Vector2i vertexTwo;
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
	visNode.setFillColor(Color::Blue);
	visNode.setOrigin(6, 6);
	visNode.setScale(3, 3);

	//Visual edge
	RectangleShape primitiveLine;

	//Storage vectors for visual vertices and edges

	vector<Vector2i> verticesVector;            //vertices
	vector<VertexArray> edgesVector;         //edges
	vector<VertexArray> linkedVector;      //edges for MST

	//Temporary active vertex storage vector
	vector<Vector2i> activeTemp;

	//Vectors for mathematical calculation
	vector<Node> nodeVect;
	vector<Edge> edgeVect;

	//Bool for starting the calculations
	bool calcStarted = false;

	//Declarations for important vars
	int delayAmount = 0;
	int solutionIndex = 0;
	int tweight = 0;

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

						for (int i = 0; i < verticesVector.size(); i++)
						{
							/*If two points are two closeand may intersect then it's not a valid position and
							the edge is not added */

							if (sqrt(pow((localPosition.x - verticesVector[i].x), 2) + pow((localPosition.y - verticesVector[i].y), 2)) < 100)
							{
								validPos = false;
							}
						}

						if (validPos)
						{
							//Add vertex (node) to main vector
							verticesVector.push_back(localPosition);

							//Update the Node Vector
							Node newNode;
							newNode.TreeID = treeID;
							treeID++;

							newNode.Xpos = localPosition.x;
							newNode.Ypos = localPosition.y;

							nodeVect.push_back(newNode);

							cout << "- Vertex Added -" << endl;
							cout << "X - Position: " << newNode.Xpos << endl;
							cout << "Y - Position: " << newNode.Ypos << endl;
							cout << "TreeID: " << treeID << endl;
							cout << endl << endl;
						}
					}

					//Right click to add edge
					if (event.key.code == Mouse::Right)
					{
						//Search for the closest local vertex and set it as active
						for (int i = 0; i < verticesVector.size(); i++)
						{
							//Calculating distance to find the closest vertex (node)
							if (sqrt(pow((localPosition.x - verticesVector[i].x), 2) + pow((localPosition.y - verticesVector[i].y), 2)) < 100)
							{
								if (activeTemp.size() < 2)
								{

									if (activeTemp.size() == 1)
									{
										if (activeTemp[0] != verticesVector[i])
										{
											activeTemp.push_back(verticesVector[i]);

											//Clear the "active temporary" vector after the edge is added to the edgesVector
											VertexArray tempLine(Lines, 2);

											tempLine[0].position = Vector2f(activeTemp[1].x, activeTemp[1].y);
											tempLine[1].position = Vector2f(activeTemp[0].x, activeTemp[0].y);

											tempLine[0].color = Color::Red;
											tempLine[1].color = Color::Red;

											edgesVector.push_back(tempLine);

											activeTemp.clear();

											//Add the new edge to the Edges Vector, make sure it doesn't already exist
											bool valid = true;
											for (int i = 0; i < edgeVect.size(); i++)
											{
												if ((edgeVect[i].vertexOne.x == activeTemp[1].x) && (edgeVect[i].vertexOne.y == activeTemp[1].y))
												{
													if (((edgeVect[i].vertexTwo.x == activeTemp[0].x) && (edgeVect[i].vertexTwo.y == activeTemp[0].y)))
													{
														valid = false;
													}
												}

												if ((edgeVect[i].vertexTwo.x == activeTemp[1].x) && (edgeVect[i].vertexTwo.y == activeTemp[1].y))
												{
													if (((edgeVect[i].vertexOne.x == activeTemp[0].x) && (edgeVect[i].vertexOne.y == activeTemp[0].y)))
													{
														valid = false;
													}
												}
											}

											//No duplicates found, add the edge to the Vector

											if (valid)
											{
												Edge newEdge;

												cout << "enter the weight of the edge\n";
												cin >> newEdge.weight;

												newEdge.vertexOne.x = activeTemp[1].x;
												newEdge.vertexOne.y = activeTemp[1].y;

												newEdge.vertexTwo.x = activeTemp[0].x;
												newEdge.vertexTwo.y = activeTemp[0].y;

												edgeVect.push_back(newEdge);

												//Output Edge Data to the console
												cout << "- Edge Created --" << endl;
												cout << "Vertex - 1: " << activeTemp[1].x << " " << activeTemp[1].y << endl;
												cout << "Vertex - 2: " << activeTemp[0].x << " " << activeTemp[0].y << endl;
												cout << "Weight: " << newEdge.weight << endl;
												cout << endl<< endl;
											}
										}
									}

									else
									{
										activeTemp.push_back(verticesVector[i]);
									}
								}
							}
						}
					}
				}
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Space)
				{
					delayAmount = 500;

					
					if (!calcStarted)
					{
						//Sort the edge Vector from small to large using insertion sort
						for (int i = 1; i < edgeVect.size(); i++)
						{
							Edge key = edgeVect[i];
							int j = i - 1;

							while (j >= 0 && edgeVect[j].weight > key.weight)
							{
								edgeVect[j + 1] = edgeVect[j];
								j = j - 1;
							}
							edgeVect[j + 1] = key;
						}
					}

					//Prevent additional nodes from being added and Start the Calculation
					calcStarted = true;
				}
			}
		}

		//Calculations
		if (calcStarted)
		{
			for (int i = 0; i < nodeVect.size(); i++)
			{
				if (edgeVect[solutionIndex].vertexOne.x == nodeVect[i].Xpos)
				{
					if (edgeVect[solutionIndex].vertexOne.y == nodeVect[i].Ypos)
					{
						for (int j = 0; j < nodeVect.size(); j++)
						{
							if (edgeVect[solutionIndex].vertexTwo.x == nodeVect[j].Xpos)
							{
								if (edgeVect[solutionIndex].vertexTwo.y == nodeVect[j].Ypos)
								{
									if (nodeVect[j].TreeID != nodeVect[i].TreeID)
									{
										//Convert all nodes to the new treeID preventing loop creation in the next iteration
										for (int y = 0; y < nodeVect.size(); y++)
										{
											if ((nodeVect[y].TreeID == nodeVect[j].TreeID) && j != y)
											{
												nodeVect[y].TreeID = nodeVect[i].TreeID;
											}
										}
										nodeVect[j].TreeID = nodeVect[i].TreeID;

										//Add a new green overlay to the linkedVector
										VertexArray tempLine(Lines, 2);

										tempLine[0].position = Vector2f(edgeVect[solutionIndex].vertexOne.x, edgeVect[solutionIndex].vertexOne.y);
										tempLine[1].position = Vector2f(edgeVect[solutionIndex].vertexTwo.x, edgeVect[solutionIndex].vertexTwo.y);

										tweight += edgeVect[solutionIndex].weight;

										tempLine[0].color = Color::Green;
										tempLine[1].color = Color::Green;

										linkedVector.push_back(tempLine);
									}
								}
							}
						}
					}
				}
			}

			//Increment the solution index (Edge to check in the next iteration)
			solutionIndex++;

			//There are (V-1) edges in the spanning tree, our calculations are done
			if (solutionIndex == nodeVect.size())
			{
				cout << "total weight (cost) for MST = " << tweight;
			}
		}

			//-- Delay Section (Only Active When Calculating) --//

			Sleep(delayAmount);

			mainWindow.clear(Color::Black);

			//Draw all the given edges and vertices
			for (int i = 0; i < edgesVector.size(); i++)
			{
				mainWindow.draw(edgesVector[i]);
			}

			for (int i = 0; i < linkedVector.size(); i++)
			{
				mainWindow.draw(linkedVector[i]);
			}

			for (int i = 0; i < verticesVector.size(); i++)
			{
				visNode.setPosition(verticesVector[i].x, verticesVector[i].y);
				mainWindow.draw(visNode);
			}

			//Call the display method
			mainWindow.display();
		}
		return 0;
}