#include "stdafx.h"
#include "Bullet.h"

#include "Enemy.h"

namespace
{
	const Vector3 SCALE = {0.5f,0.5f,0.5f};
	const float BULLET_SPPED = 10.0f;
	
	const float CURVATURE_RADIUS = 30.0f;
	const float DAMPING = 0.1f;
}


bool Bullet::Start()
{
	m_modelRender.Init("Assets/modelData/box.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	return true;
}

void Bullet::Update()
{
	MoveBullet();
	Inpact();
	m_modelRender.Update();
}


void Bullet::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Bullet::MoveBullet()
{
	CalcVelocity(BULLET_SPPED, CURVATURE_RADIUS, DAMPING);
	m_position += m_velocity;
	m_modelRender.SetPosition(m_position);
}

//ˆÈ‰º‚ðŽQÆ
//https://techblog.kayac.com/tracking-calculation-of-homing-laser
void Bullet::CalcVelocity(const float speed, const float curvatureRadius,
	const float damping)
{
	float maxCentripetalAccel = speed * speed / curvatureRadius;
	float propulsion = speed * damping;

	Vector3 targetPosition = m_targetPosition;
	Vector3 toTarget = targetPosition - m_position;
	Vector3 vn = m_velocity;
	vn.Normalize();
	float dot = toTarget.Dot(vn);
	Vector3 centripetalAccel = toTarget - (vn * dot);
	float centripetalAccelMagnitude = centripetalAccel.Length();
	if (centripetalAccelMagnitude > 1.0f)
	{
		centripetalAccel /= centripetalAccelMagnitude;
	}
	Vector3 force = centripetalAccel * curvatureRadius;
	force += vn * propulsion;
	force -= m_velocity * damping;
	m_velocity += force * g_gameTime->GetFrameDeltaTime();
}

void Bullet::Inpact()
{
	Vector3 diff = m_targetPosition - m_position;
	if (diff.LengthSq() >= 30.0f * 30.0f)
	{
		return;
	}
	DeleteGO(this);
}
