#include "Camera.h"

#include "Time.h"
#include "Event.h"

#include <algorithm>

Camera::Camera() : moveSpeed(0), rotationSpeed(0), pitch(0), yaw(0) {
}

Camera::Camera(float FOV, float aspectRatio, float nearZ, float farZ, float rotationSpeed, float moveSpeed, Vector3 position, Vector3 forward, Vector3 up)
	: position(position), forward(forward), direction(forward), up(up), moveSpeed(moveSpeed), rotationSpeed(rotationSpeed), pitch(0), yaw(0), FOV(FOV), nearZ(nearZ), farZ(farZ)
{
	this->viewMatrix = Matrix::CreateLookAt(position, forward, up);
	this->perspectiveMatrix = Matrix::CreatePerspectiveFieldOfView(FOV, aspectRatio, nearZ, farZ);
	camRay = std::make_shared<RayCollider>();
}

void Camera::MoveUp(int sign)
{
	position.y += moveSpeed * Time::GetDelta() * sign * speedMultiplier;
}

void Camera::MoveRight(int sign)
{
	Vector3 forwardVec;
	Vector3::Transform(forward, Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f), forwardVec);

	Vector3 rightVec = up.Cross(forwardVec);
	rightVec.Normalize();

	position += rightVec * Time::GetDelta() * moveSpeed * (float)sign * speedMultiplier;
}

void Camera::MoveForward(int sign)
{
	Vector3 forwardVec;
	Vector3::Transform(forward, Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f), forwardVec);
	forwardVec.Normalize();

	position += forwardVec * Time::GetDelta() * moveSpeed * (float)sign * speedMultiplier;
}

void Camera::Rotate(float dx, float dy)
{
	//YAW
	yaw = (yaw + dx * Time::GetDelta() * rotationSpeed);

	if (yaw < 0.0f)
		yaw += PI * 2.0f;
	if (yaw > PI * 2.0f)
		yaw -= PI * 2.0f;

	//PITCH
	pitch = std::clamp(pitch + dy * Time::GetDelta() * rotationSpeed, 0.995f * -PI_DIV2, 0.995f * PI_DIV2);
}

void Camera::SetSpeedMultiplier(float xSpeed)
{
	speedMultiplier = xSpeed;
}

void Camera::SetPerspectiveMatrix(float width, float height)
{
	this->perspectiveMatrix = Matrix::CreatePerspectiveFieldOfView(FOV, width / height, nearZ, farZ);
}

void Camera::UpdatePosOnly()
{
	const Vector3 target = position + direction;

	viewMatrix = Matrix::CreateLookAt(position, target, up);
}

void Camera::Update()
{
	Vector3 lookAt;
	Vector3::Transform(forward, Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f), lookAt);
	lookAt.Normalize();

	direction = lookAt;

	const Vector3 target = position + lookAt;

	viewMatrix = Matrix::CreateLookAt(position, target, up);
}

void Camera::RotateAroundPoint(Vector3 target, float distance, Vector3 direction)
{
	static float angle = 0;
	angle += Time::GetDelta() * 0.3f;
	const float x = cos(angle);
	const float z = sin(angle);

	direction = Vector3(x, direction.y, z);
	position = target - direction * distance;
	viewMatrix = Matrix::CreateLookAt(position, target, { 0, 1, 0 });



}
