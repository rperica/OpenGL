#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
	:m_Position(position),m_Direction(0.0f,0.0f,-1.0f),m_Up(worldUp),
	 m_sensivity(SENSIVITY),m_speed(SPEED),m_zoom(ZOOM),
	 m_yaw(yaw),m_pitch(pitch),m_WorldUp(worldUp)
{
	UpdateCamera();
}

Camera::~Camera()
{
	//...
}

glm::mat4 Camera::View() const
{
	return glm::lookAt(m_Position,m_Position+m_Direction,m_Up);
}

void Camera::UpdateCamera()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	
	m_Direction = glm::normalize(direction);
	m_Right = glm::normalize(glm::cross(m_Direction, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Direction));
}

void Camera::KeyboardInput(cameraMovement moveDirection,float deltaTime)
{
	float velocity = m_speed * deltaTime;
	if (moveDirection == FORWARD)
		m_Position += m_Direction * velocity;
	else if (moveDirection == BACKWARD)
		m_Position -= m_Direction * velocity;
	else if (moveDirection == LEFT)
		m_Position -= m_Right * velocity;
	else if (moveDirection == RIGHT)
		m_Position += m_Right * velocity;
}

void Camera::MouseProcess(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= m_sensivity;
	yoffset *= m_sensivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	UpdateCamera();
}

void Camera::ScrollProcess(float yoffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= yoffset;
	if (m_zoom <= 1.0f)
		m_zoom = 1.0f;
	if (m_zoom >= 45.0f)
		m_zoom = 45.0f;
}

