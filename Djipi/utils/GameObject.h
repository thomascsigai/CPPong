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
		string m_Name;
		Transform m_Transform;
		int velX = 0, velY = 0;

	public:
		GameObject() {}
		GameObject(string name) : m_Name(name) {}
		GameObject(string name, int x, int y) { m_Transform.x = x; m_Transform.y = y; }

		virtual void Render(SDL_Renderer* renderer)
		{
			SDL_FRect rect = { m_Transform.x, m_Transform.y, m_Transform.w, m_Transform.h };
			SDL_RenderFillRectF(renderer, &rect);


			//Debug draw collider
			/*SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawRectF(renderer, &transform.collider);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);*/
		}

		virtual void Move(double deltaTime)
		{
			m_Transform.x += velX * deltaTime;
			m_Transform.y += velY * deltaTime;

			m_Transform.UpdateCollider();
		}

		virtual void OnCollide(GameObject& other)
		{
			cout << m_Name << "Collided with " << other.m_Name << "." << endl;
		}

		virtual void HandleEvent(SDL_Event& e)
		{
			cerr << "HandleEvent method used but not implemented for GameObject " << m_Name << "." << endl;
		}


		// Getters
		Transform GetTransform() const { return m_Transform; }
		string GetName() const { return m_Name; }
		SDL_FRect GetCollider() const { return m_Transform.collider; }

		//Setters
		void SetName(string name) { m_Name = name; }
	};
}