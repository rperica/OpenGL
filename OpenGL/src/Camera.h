#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum cameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;
const float SPEED = 2.5f;
const float SENSIVITY = 0.1f;

class Camera
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
	glm::vec3 m_WorldUp;

	float m_yaw;
	float m_pitch;
	float m_speed;
	float m_sensivity;
	float m_zoom;

	void UpdateCamera();

public:
	Camera(glm::vec3 position= glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 worldUp=glm::vec3(0.0f,1.0f,0.0f),float yaw=YAW,float pitch=PITCH);
	~Camera();

	glm::mat4 View() const;
	
	void KeyboardInput(cameraMovement moveDirection,float deltaTime);
	void MouseProcess(float xoffset,float yoffset,bool constrainPitch=true);
	void ScrollProcess(float yoffset);

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::vec3& GetFront() const { return m_Direction; }
	inline const glm::vec3& GetUP() const { return m_WorldUp; }
	inline const float& GetZoom()const { return m_zoom; }
};
