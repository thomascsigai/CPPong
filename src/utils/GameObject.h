#pragma once

#include <iostream>

using namespace std;

struct Transform
{
	int x = 0, y = 0;
	int w = 0, h = 0;

	SDL_Rect collider = {};

	void SetPosition(int _x, int _y)
	{
		x = _x; y = _y;
		UpdateCollider();
	}

	void SetSize(int _w, int _h)
	{
		w = _w; h = _h;
		UpdateCollider();
	}

	void UpdateCollider() { collider = { x, y, w, h }; }
};


class GameObject
{
protected:
	string name;
	Transform transform;
	int velX = 0, velY = 0;

public:
	GameObject() {}
	GameObject(int x, int y) { transform.x = x; transform.y = y; }

	virtual void Render(SDL_Renderer* renderer)
	{
		cerr << "Render method used but not implemented for GameObject " << name << "." << endl;
	}

	virtual void Move()
	{
		transform.x += velX;
		transform.y += velY;

		transform.UpdateCollider();
	}

	virtual void OnCollide(GameObject other)
	{
		cout << name << "Collided with " << other.name << "." << endl;
	}


	// Getters
	Transform GetTransform() const { return transform; }
	string GetName() const { return name; }
	SDL_Rect GetCollider() const { return transform.collider; }

	//Setters
	void SetName(string name) { name = name; }
};