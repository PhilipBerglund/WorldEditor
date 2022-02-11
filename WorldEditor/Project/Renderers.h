#pragma once
#include "ColliderRenderer.h"			//CR
#include "IDRenderer.h"					//IDR
#include "ModelRenderer.h"				//MR
#include "ShadowRenderer.h"				//SR
#include "TerrainRenderer.h"			//TR
#include "VolumeRenderer.h"				//VR
#include "WaterRenderer.h"				//WR
#include "SkyBoxRenderer.h"				//SBR
#include "PerformanceRenderer.h"		//PFR

class Renderers : public Singleton<Renderers>
{
private:
	static ColliderRenderer* cr;
	static IDRenderer* idr;
	static ModelRenderer* mr;
	static ModelRenderer* smr;
	static ShadowRenderer* sr;
	static TerrainRenderer* tr;
	static VolumeRenderer* vr;
	static WaterRenderer* wr;
	static SkyBoxRenderer* sbr;
	static PerformanceRenderer* pfr;
public:
	Renderers() :Singleton(this) {}
	~Renderers() { ShutDown(); }


	static void InitColliderRenderer()																	{ cr = new ColliderRenderer(); }
	static void InitIDRenderer()																		{ idr = new IDRenderer(); }
	static void InitModelRenderer(bool isLit = true)													{ mr = new ModelRenderer(isLit); }
	static void InitStaticModelRenderer(bool isLit = true)												{ smr = new ModelRenderer(isLit); }
	static void InitShadowRenderer()																	{ sr = new ShadowRenderer(); }
	static void InitTerrainRenderer(float tesselationAmount = 63.0f)									{ tr = new TerrainRenderer(tesselationAmount); }
	static void InitVolumeRenderer()																	{ vr = new VolumeRenderer(); }
	static void InitWaterRenderer(float tesselationAmount = 63.0f)										{ wr = new WaterRenderer(tesselationAmount); }
	static void InitSkyBoxRenderer()																	{ sbr = new SkyBoxRenderer(); }
	static void InitSkyBoxRenderer(std::string skyBoxDayFolderName, std::string skyBoxNightFolderName)  { sbr = new SkyBoxRenderer(skyBoxDayFolderName, skyBoxNightFolderName); }
	static void InitPerformanceRenderer() { pfr = new PerformanceRenderer(); }

	static ColliderRenderer* CR()		{ return cr; }
	static IDRenderer* IDR()			{ return idr; }
	static ModelRenderer* MR()			{ return mr; }
	static ModelRenderer* SMR()			{ return smr; }
	static ShadowRenderer* SR()			{ return sr; }
	static TerrainRenderer* TR()		{ return tr; }
	static VolumeRenderer* VR()			{ return vr; }
	static WaterRenderer* WR()			{ return wr; }
	static SkyBoxRenderer* SBR()		{ return sbr; }
	static PerformanceRenderer* PFR()	{ return pfr; }

	static void Clear()
	{
		if (cr)
			cr->Clear();
		if (idr)
			idr->Clear();
		if (mr)
			mr->Clear();
		if (smr)
			smr->Clear();
		if (sr)
			sr->Clear();
		if (vr)
			vr->Clear();
		if (wr)
			wr->Clear();
		if (sbr)
			sbr->Clear();
		if (pfr)
			pfr->Clear();
	}
	static void ShutDown()
	{
			
		if (cr)
		{
			delete cr;
			cr = nullptr;
		}
			
		if (idr)
		{
			delete idr;
			idr = nullptr;
		}
			
		if (mr)
		{
			delete mr;
			mr = nullptr;
		}
			
		if (smr)
		{
			delete smr;
			smr = nullptr;
		}
			
		if (sr)
		{
			delete sr;
			sr = nullptr;
		}
			
		if (tr)
		{
			delete tr;
			tr = nullptr;
		}
			
		if (vr)
		{
			delete vr;
			vr = nullptr;
		}
			
		if (wr)
		{
			delete wr;
			wr = nullptr;
		}

		if (sbr)
		{
			delete sbr;
			sbr = nullptr;
		}

		if (pfr)
		{
			delete pfr;
			pfr = nullptr;
		}
	}
};
inline ColliderRenderer*		Renderers::cr	= nullptr;
inline IDRenderer*				Renderers::idr	= nullptr;
inline ModelRenderer*			Renderers::mr	= nullptr;
inline ModelRenderer*			Renderers::smr	= nullptr;
inline ShadowRenderer*			Renderers::sr	= nullptr;
inline TerrainRenderer*			Renderers::tr	= nullptr;
inline VolumeRenderer*			Renderers::vr	= nullptr;
inline WaterRenderer*			Renderers::wr	= nullptr;
inline SkyBoxRenderer*			Renderers::sbr	= nullptr;
inline PerformanceRenderer*		Renderers::pfr = nullptr;

inline Renderers& GetRenderersInstance() { return Renderers::Inst(); }
#define RND GetRenderersInstance()

inline ColliderRenderer* RendererCR() { return RND.CR(); }
//COLLIDER RENDERER
#define CR RendererCR()

inline IDRenderer* RendererIDR() { return RND.IDR(); }
//ANIMATED MODEL RENDERER
#define IDR RendererIDR()

inline ModelRenderer* RendererMR() { return RND.MR(); }
//MODEL RENDERER
#define MR RendererMR()

inline ModelRenderer* RendererSMR() { return RND.SMR(); }
//MODEL RENDERER
#define SMR RendererSMR()

inline ShadowRenderer* RendererSR() { return RND.SR(); }
//SHADOW RENDERER
#define SR RendererSR()

inline TerrainRenderer* RendererTR() { return RND.TR(); }
//TERRAIN RENDERER
#define TR RendererTR()

inline VolumeRenderer* RendererVR() { return RND.VR(); }
//VOLUME RENDERER	
#define VR RendererVR()

inline WaterRenderer* RendererWR() { return RND.WR(); }
//WATER RENDERER
#define WR RendererWR()

inline SkyBoxRenderer* RendererSBR() { return RND.SBR(); }
//SKYBOX RENDERER
#define SBR RendererSBR()

inline PerformanceRenderer* RendererPFR() { return RND.PFR(); }
//PERFORMANCE RENDERER
#define PFR RendererPFR()