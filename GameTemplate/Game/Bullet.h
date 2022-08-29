#pragma once

class Enemy;

class Bullet : public IGameObject
{
public:
	Bullet(){}
	~Bullet(){}
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetVelocity(const Vector3& velocity)
	{
		m_velocity = velocity;
	}
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	void SetTarget(const Vector3& targetPosition)
	{
		m_targetPosition = targetPosition;
	}
private:
	void CalcVelocity(const float speed, const float curvatureRadius,
		const float damping);
	void MoveBullet();
	void Inpact();
private:
	ModelRender	m_modelRender;
	Vector3 m_position;
	Vector3 m_velocity;
	Vector3 m_targetPosition;
};

