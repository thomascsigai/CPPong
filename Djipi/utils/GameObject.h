#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

namespace Djipi
{
	struct Transform
	{
		float x = 0, y = 0;
		float w = 0, h = 0;

		SDL_FRect collider = {};

		void SetPosition(float _x, float _y)
		{
			x = _x; y = _y;
			UpdateCollider();
		}

		void SetSize(float _w, float _h)
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
			SDL_FRect rect = { transform.x, transform.y, transform.w, transform.h };
			SDL_RenderFillRectF(renderer, &rect);


			//Debug draw collider
			/*SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawRectF(renderer, &transform.collider);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);*/
		}

		virtual void Move(double deltaTime)
		{
			transform.x += velX * deltaTime;
			transform.y += velY * deltaTime;

			transform.UpdateCollider();
		}

		virtual void OnCollide(GameObject& other)
		{
			cout << name << "Collided with " << other.name << "." << endl;
		}

		virtual void HandleEvent(SDL_Event& e)
		{
			cerr << "HandleEvent method used but not implemented for GameObject " << name << "." << endl;
		}


		// Getters
		Transform GetTransform() const { return transform; }
		string GetName() const { return name; }
		SDL_FRect GetCollider() const { return transform.collider; }

		//Setters
		void SetName(string name) { name = name; }
	};
}