#include "Scene.h"
#include "ShaderData.h"
#include "Event.h"

#include <filesystem>

std::vector<std::string> &Scene::GetObjectNames()
{
	return objectNames;
}

std::string Scene::AddDrawable(const std::string& name, std::shared_ptr<Drawable> drawable)
{
	UINT numInstances = 0;
	std::string finalName = name;

	for (auto& [name, drawable] : drawables)
		if (name.find(finalName) != std::string::npos)
			numInstances++;

	if (numInstances > 0)
	{
		finalName = finalName + std::to_string(numInstances);
		drawable->SetName(finalName);
	}
		
	drawables[finalName] = drawable;
	objectNames.push_back(finalName);

	return finalName;
}

std::string Scene::AddDrawable(std::shared_ptr<Drawable> drawable)
{
	drawables[drawable->GetName()] = drawable;

	return drawable->GetName();
}

std::string Scene::AddModel(const std::string& file, const std::string path)
{
	UINT numInstances = 0;
	std::string fileName = file;

	for (auto& [name, drawable] : drawables)
		if (name.find(file) != std::string::npos)
			numInstances++;

	if (numInstances > 0)
	{
		fileName = file + std::to_string(numInstances);
		drawables[fileName] = std::make_shared<Model>(fileName, *std::dynamic_pointer_cast<Model>(drawables[file]));
	}
	else
		drawables[fileName] = std::make_shared<Model>(file, fileName);
		
	objectNames.push_back(fileName);

	drawables[fileName]->SetName(fileName);

	return fileName;
}

std::string Scene::AddModel(std::string fileName, const std::string& file, const std::string path)
{
	UINT numInstances = 0;

	for (auto& [name, drawable] : drawables)
		if (name.find(file) != std::string::npos)
			numInstances++;

	if (numInstances > 0)
	{
		fileName = file + std::to_string(numInstances);
		drawables[fileName] = std::make_shared<Model>(fileName, *std::dynamic_pointer_cast<Model>(drawables[file]));
	}
	else
		drawables[fileName] = std::make_shared<Model>(file, fileName);

	objectNames.push_back(fileName);

	drawables[fileName]->SetName(fileName);

	return fileName;
}

void Scene::AddModel(const std::string& name, std::shared_ptr<Drawable> drawable)
{
	drawables[name] = drawable;
	objectNames.push_back(name);
	drawables[name]->SetName(name);
}

void Scene::AddBoundingVolume(const std::string& name, std::shared_ptr<Drawable> drawable)
{
	drawables[name] = drawable;
	objectNames.push_back(name);
	drawables[name]->SetName(name);
}

void Scene::AddPointLight(Vector3 position, float range, Vector3 attenuation, Vector4 color)
{
	if (pointLights.size() < MAX_LIGHTS)
		pointLights.push_back(PointLight(range, attenuation, color, position));
}

void Scene::UpdatePointLights()
{
	for (auto& pointlight : pointLights)
	{
		pointlight.Update();
	}
}


void Scene::SetDirectionalLight(float range, Vector4 color, float startAngle, int startDir)
{
	directionalLight = DirectionalLight(range, color, startAngle, startDir);
}

void Scene::SetCamera(float FOV, float aspectRatio, float nearZ, float farZ, float rotationSpeed, float moveSpeed, Vector3 position, Vector3 forward, Vector3 up)
{
	camera = new Camera(FOV, aspectRatio, nearZ, farZ, rotationSpeed, moveSpeed, position, forward, up);
}

void Scene::Update()
{
	//camera->Update();
	//directionalLight.Update();

	for (auto& [name, drawable] : drawables)
	{
		drawable->Update();
	}

	//ShaderData::Inst().Update(*camera, directionalLight, (UINT)pointLights.size(), nullptr);
}