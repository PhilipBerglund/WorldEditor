#include "PlaneWithNormals.h"

PlaneWithNormals::PlaneWithNormals(UINT subdivisions, UINT size)
{
	const UINT cells = (UINT)pow(2, subdivisions);
	const UINT numTris = (UINT)pow(2, subdivisions * 2 + 1);
	const float triSize = (float)size / (float)cells;
	const float texSize = 1.0f / (float)cells;

	Vector3 position;
	Vector2 texCoords;
	Vector3 normal;
	Vector3 tangent;
	std::vector<Vertex> vertices;

	for (UINT i = 0; i < cells + 1; ++i)
	{
		for (UINT j = 0; j < cells + 1; ++j)
		{
			position = { triSize * i - (size / 2) , 0, triSize * j - (size / 2) };
			texCoords = { texSize * i + (1.0f / size), texSize * j };
			//ADD VALUE FOR NORMAL AND TANGENT
			normal = { 0,0,-1 };
			tangent = { 0,0,1 };

			vertices.emplace_back(Vertex{ position, texCoords, normal, tangent });
		}
	}

	const UINT offset = cells + 1;
	std::vector<UINT> indices;

	for (UINT i = 0; i < cells; ++i)
	{
		for (UINT j = 0; j < cells; ++j)
		{
			indices.emplace_back(i * offset + j);
			indices.emplace_back(j + (i * offset) + 1);
			indices.emplace_back(j + 1 + offset + offset * i);
			indices.emplace_back(j + 1 + offset + offset * i);
			indices.emplace_back(offset + i * offset + j);
			indices.emplace_back(i * offset + j);
		}
	}

	//VERTICES
	CreateVertexBuffer(vertexBuffer, sizeof(Vertex), (UINT)vertices.size() * sizeof(Vertex), vertices.data());

	//INDICES
	indexCount = (UINT)indices.size();
	CreateIndexBuffer(indexBuffer, (UINT)indices.size(), indices.data());
}

PlaneWithNormals::~PlaneWithNormals()
{
	indexBuffer->Release();
	vertexBuffer->Release();
}

void PlaneWithNormals::Draw()
{
	Graphics::Inst().GetContext().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	Graphics::Inst().GetContext().IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	Graphics::Inst().GetContext().DrawIndexed(indexCount, 0, 0);
	Graphics::Inst().GetContext().IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
}
