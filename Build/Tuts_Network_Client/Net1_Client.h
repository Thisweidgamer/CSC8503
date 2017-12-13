
#pragma once

#include <ncltech\Scene.h>
#include <ncltech\NetworkBase.h>
#include "MazeGenerator.h"
#include "ClientFunctions.h"
#include "MazeRenderer.h"
#include <nclgl\OBJMesh.h>


#define ID serverConnection->outgoingPeerID
#define OUT_OF_RANGE -1
//Basic Network Example

class Net1_Client : public Scene
{
public:
	Net1_Client(const std::string& friendly_name);

	virtual void OnInitializeScene() override;
	virtual void OnCleanupScene() override;
	virtual void OnUpdateScene(float dt) override;
	virtual bool foundServer() { return (serverConnection != NULL); }

	void ProcessNetworkEvent(const ENetEvent& evnt);

	// Recieving Packets
	void ApplyMaze(MazeStruct m);

	// Sending Packets
	void SendStartPosition();
	void SendEndPosition();
	void RequestNewMaze();
	void SendAvatarLocation();
	
	// Helper Math
	Vector3 Pos_To_Maze(Vector3 pos);
	Vector3 Maze_Scale();

	// Callback function for selecting starting & ending position
	void ClickableLocationCallback(int idx);

	//Get Server connection;
	ENetPeer* getPeer() { return serverConnection; }

	// Handle Keyboard Inputs which require to edit data stored in this class
	void HandleKeyboardInputs();

	bool isDrawingTiles() { return drawTiles; }

protected:
	// Network
	NetworkBase network;
	ENetPeer*	serverConnection;

	// Maze
	MazeGenerator* generator;
	MazeRenderer* maze;
	Mesh* wallmesh;
	int size = 10;
	float density = 0.5f;

	// Debug Draw bools
	bool drawPath = false;
	bool drawMesh = false;
	bool drawTiles = false;

	// Number of clients connected to this client's server - used for drawing
	int clients;

	// Path Generated by Astar
	std::list<const GraphNode*> path;

	// Indeces indicating all avatars' positions
	vector<int> avatars;
	vector<Vector3> avatar_positions;
};