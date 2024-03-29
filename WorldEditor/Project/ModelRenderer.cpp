#include "ModelRenderer.h"
#include "Model.h"

ModelRenderer::ModelRenderer(bool isLit)
	:isLit(isLit)
{
	//BUFFER
	CreateBuffer(matricesBuf, sizeof(Matrices));
	CreateBuffer(fogBuf, sizeof(FogData));


	//SHADERS
	std::string byteCode;

	if (isLit)
	{
		if (!LoadShader(vertexShader, vs_path, byteCode))
			return;

		if (!LoadShader(pixelShader, forward_ps_path))
			return;
	}

	else
	{
		if (!LoadShader(vertexShader, unlit_vs_path, byteCode))
			return;

		if (!LoadShader(pixelShader, unlit_forward_ps_path))
			return;
	}

	Print("SUCCEEDED LOADING SHADERS", "MODEL RENDERER");

	//INPUT LAYOUT
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXTURECOORDS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	HRESULT hr = Graphics::Inst().GetDevice().CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), byteCode.c_str(), byteCode.length(), &inputLayout);
	if FAILED(hr)
	{
		Print("FAILED TO CREATE INPUT LAYOUT", "MODEL RENDERER");
		return;
	}
	Print("SUCCEEDED TO CREATE INPUT LAYOUT", "MODEL RENDERER");

	Print("SUCCEEDED TO INITIALIZE MODEL RENDERER");
	Print("=======================================");
}

ModelRenderer::~ModelRenderer()
{
	matricesBuf->Release();
	vertexShader->Release();
	pixelShader->Release();
	inputLayout->Release();
	fogBuf->Release();
}

void ModelRenderer::Render()
{
	if (drawables.empty())
		return;

	//INPUT LAYOUT
	Graphics::Inst().GetContext().IASetInputLayout(inputLayout);

	//TOPOLOGY
	Graphics::Inst().GetContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//SHADERS
	BindShaders(vertexShader, nullptr, nullptr, nullptr, pixelShader);

	//SAVE SHADER DATA INSTANCE
	auto& shaderData = ShaderData::Inst();

	matrices.viewPerspective = shaderData.cameraMatrix;
	matrices.lightViewPerspective = shaderData.lightMatrix;

	for (auto& drawable : drawables)
	{
		auto model = std::dynamic_pointer_cast<Model>(drawable);
		if (!model)
			continue;

		Timer timer;
		timer.Start();
		matrices.world = model->GetMatrix();

		UpdateBuffer(matricesBuf, matrices);
		BindBuffer(matricesBuf);
		BindBuffer(fogBuf, Shader::PS, 4);


		if (isLit)
			model->Draw();
		else
			model->Draw(true, false);
		model->SetTTD(timer.DeltaTime());
	}
}

void ModelRenderer::UpdateFog(float fStart, float fRange, float fCScale)
{
	fogData.start = fStart;
	fogData.range = fRange;
	fogData.color = fCScale;
	UpdateBuffer(fogBuf, fogData);
	BindBuffer(fogBuf, Shader::PS, 4);
	Print("Inside Update Fog!");
}
