//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "Keyboard.h"
#include "MathEngine.h"
#include "MathApp.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectAnimSkin.h"
#include "ShaderObject.h"
#include "ProtoMesh.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "GraphicsObject_Null.h"
#include "GraphicsObject_SkinTexture.h"
#include "TextureMan.h"
#include "InputMan.h"
#include "InputTest.h"
#include "Camera.h"
#include "Camera3D.h"
#include "Camera2D.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "ShaderMan.h"
#include "CameraMan.h"
#include "CameraMesh.h"
#include "CameraDemoInput.h"
#include "GameObjectBoundingSphere.h"
#include "AnimTimer.h"
#include "Anim.h"
#include "TimerController.h"
#include "AnimController.h"
#include "Clip.h"
#include "ImageMan.h"
#include "GraphicsObject_Sprite.h"
#include "SpriteMesh.h"
#include "GameObject2D.h"
#include "GameObjectBasic.h"
#include "SSBO.h"
#include "Mixer.h"
#include "WorldCompute.h"
#include "AnimMan.h"

using namespace Azul;

namespace Azul
{
	// Todo: clean up
	Keyboard myKeyboard;
	AnimController *pMouseAnimController;
	AnimController* pMouseAnimController2;
	AnimController* pMouseAnimController3;
	AnimController* pMouseAnimController4;
	AnimController* pMouseAnimController5;

	Mixer *pMouseMixer;
	Mixer *pMouseMixer2;
	Mixer *pMouseMixer3;
	Mixer* pMouseMixer4;
	Mixer* pMouseMixer5;

	AnimController* pChickenAnimController;
	AnimController* pChickenAnimController2;
	AnimController* pChickenAnimController3;
	AnimController* pChickenAnimController4;

	Mixer* pChickenMixer;
	Mixer* pChickenMixer2;
	Mixer* pChickenMixer3;
	Mixer* pChickenMixer4;

	WorldCompute *pMouseWorldCompute;
	WorldCompute *pChickenWorldCompute;

	//-----------------------------------------------------------------------------
	//  Game::Game()
	//		Game Engine Constructor
	//-----------------------------------------------------------------------------
	Game::Game(const char *const pWindowName, const int Width, const int Height)
		:Engine(pWindowName, Width, Height), 
		pProtoVersion(nullptr)
	{
		assert(pWindowName);
		this->globalTimer.Tic();
		this->intervalTimer.Tic();
	}

	//-----------------------------------------------------------------------------
	//  Game::~Game()
	//		Game Engine destructor
	//-----------------------------------------------------------------------------
	Game::~Game()
	{
	}

	//-----------------------------------------------------------------------------
	// Game::Initialize()
	//		Allows the engine to perform any initialization it needs to before 
	//      starting to run.  This is where it can query for any required services 
	//      and load any non-graphic related content. 
	//-----------------------------------------------------------------------------
	void Game::Initialize()
	{

	}


	//-----------------------------------------------------------------------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//-----------------------------------------------------------------------------
	void Game::LoadContent()
	{
		// Set the Asset proto version for checking.
		this->SetProtoVersion("1.1.0");

		// Start the managers
		InputMan::Create();
		TextureMan::Create();
		MeshNodeMan::Create();
		ShaderMan::Create();
		CameraMan::Create();
		GameObjectMan::Create();
		ImageMan::Create();
		AnimMan::Create();

		// --------------------------
		// Camera setup
		// --------------------------

		// Camera_0		

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 3D perspective Camera
		//---------------------------------------------------------------------------------------------------------
		Camera3D *pCam0 = new Camera3D();
		pCam0->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
		pCam0->setPerspective(35.0f, float(pCam0->getScreenWidth()) / float(pCam0->getScreenHeight()), 1.0f, 10000.0f);
		pCam0->setOrientAndPosition(Vec3(1.0f, 0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(-1.0f, 12.0f, 0.0f));
		pCam0->updateCamera();
		CameraMan::Add(Camera::Name::CAMERA_0, pCam0);
		CameraMan::SetCurrent3D(Camera::Name::CAMERA_0);

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 2D orthographic Camera
		//---------------------------------------------------------------------------------------------------------
		Camera2D *pCam2D = new Camera2D();

		pCam2D->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
		pCam2D->setOrthographic((float)-pCam2D->getScreenWidth() / 2.0f, (float)pCam2D->getScreenWidth() / 2.0f,
			(float)-pCam2D->getScreenHeight() / 2.0f, (float)pCam2D->getScreenHeight() / 2.0f,
			1.0f, 1000.0f);
		pCam2D->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));

		// Holder for the current 2D  cameras
		CameraMan::Add(Camera::Name::CAMERA_1, pCam2D);
		CameraMan::SetCurrent2D(Camera::Name::CAMERA_1);

		// -----------------------------------
		// Load the Mesh from Data file
		// -----------------------------------

		Mesh *pPyramidMesh = new ProtoMesh("PyramidMesh.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::PYRAMID, pPyramidMesh);

		Mesh *pR2D2Mesh = new ProtoMesh("R2-D2.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::R2D2, pR2D2Mesh);

		Mesh* pWoodCrateMesh = new ProtoMesh("wooden crate.mt.proto.azul", Texture::Name::CRATE);
		MeshNodeMan::Add(Mesh::Name::CRATE, pWoodCrateMesh);

		Mesh* pSpaceFrigateMesh = new ProtoMesh("space_frigate.mt.proto.azul", Texture::Name::SPACE_FRIGATE);
		MeshNodeMan::Add(Mesh::Name::SPACE_FRIGATE, pSpaceFrigateMesh);

		// Load the Sprite Mesh
		SpriteMesh *pSpriteMesh = new SpriteMesh("SpriteModel.azul");
		assert(pSpriteMesh);
		MeshNodeMan::Add(Mesh::Name::SPRITE, pSpriteMesh);


		// ----------------------------------
		// Create/Load Shader 
		// ----------------------------------
		ShaderObject *pShaderObject_sprite;
		pShaderObject_sprite = ShaderMan::Add(ShaderObject::Name::SPRITE, "spriteRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_sprite);

		ShaderObject *pShaderObject_constcolor;
		pShaderObject_constcolor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constColorRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_constcolor);

		ShaderObject *pShaderObject_color;
		pShaderObject_color = ShaderMan::Add(ShaderObject::Name::COLOR_POSITION, "colorRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_color);

		ShaderObject *pShaderObject_texture;
		pShaderObject_texture = ShaderMan::Add(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_texture);

		ShaderObject *pShaderObject_textureLight;
		pShaderObject_textureLight = ShaderMan::Add(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_textureLight);

		ShaderObject *pShaderObject_constColor;
		pShaderObject_constColor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constcolorRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_constColor);

		ShaderObject *pShaderObject_colorSingle;
		pShaderObject_colorSingle = ShaderMan::Add(ShaderObject::Name::COLOR_SINGLE, "colorSingleRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_colorSingle);

		// Load Skin
		ShaderObject *pShaderObject_SkinTexture = ShaderMan::Add(ShaderObject::Name::SKIN_TEXTURE, "skinTextureRender", ShaderObject::Type::GRAPHICS);
		AZUL_UNUSED_VAR(pShaderObject_SkinTexture);
		assert(pShaderObject_SkinTexture);

		// Compute shader
		ShaderObject *pShaderObject_compute = ShaderMan::Add(ShaderObject::Name::COMPUTE_TEST, "computeTest", ShaderObject::Type::COMPUTE);
		AZUL_UNUSED_VAR(pShaderObject_compute);
		assert(pShaderObject_compute);

		ShaderObject *pShaderObject_mixer = ShaderMan::Add(ShaderObject::Name::COMPUTE_MIXER, "computeMixer", ShaderObject::Type::COMPUTE);
		AZUL_UNUSED_VAR(pShaderObject_mixer);
		assert(pShaderObject_mixer);

		ShaderObject *pShaderObject_world = ShaderMan::Add(ShaderObject::Name::COMPUTE_WORLD, "computeWorldMatrix", ShaderObject::Type::COMPUTE);
		AZUL_UNUSED_VAR(pShaderObject_world);
		assert(pShaderObject_world);

		// ------------------------------------------
		// Load Textures from Data File
		// ------------------------------------------
		TextureMan::Add("HotPink.t.proto.azul", Texture::Name::HOT_PINK);
		TextureMan::Add("Aliens.t.proto.azul", Texture::Name::INVADERS);
		TextureMan::Add("Duckweed.t.proto.azul", Texture::Name::DUCKWEED);
		TextureMan::Add("Rocks.t.proto.azul", Texture::Name::ROCKS);
		TextureMan::Add("Stone.t.proto.azul", Texture::Name::STONES);
		TextureMan::Add("RedBrick.t.proto.azul", Texture::Name::RED_BRICK);
		TextureMan::Add("R2D2_BaseColor.t.proto.azul", Texture::Name::R2D2);
		TextureMan::Add("FontTexture.t.proto.azul", Texture::Name::TEXT);
		TextureMan::Add("Ch14_1001_Diffuse.t.proto.azul",Texture::Name::MOUSEY);
		TextureMan::Add("ChickenbotDiffuse.t.proto.azul", Texture::Name::CHICKEN_BOT);

		// -------------------------------------------
		// Images
		// -------------------------------------------

		Image* pImageGreen = new Image(Image::Name::Alien_Green, Texture::Name::INVADERS, Rect(136.0f, 64.0f, 85.0f, 63.0f));
		Image* pImageRed = new Image(Image::Name::Alien_Red, Texture::Name::INVADERS, Rect(560.0f, 64.0f, 94.0f, 63.0f));

		static_assert(sizeof(Image) == 36, "wrong size");

		assert(pImageGreen);
		ImageMan::Add(pImageGreen);
		assert(pImageRed);
		ImageMan::Add(pImageRed);

		Vec4 Yellow(1.0f, 1.0f, 1.0f, 1.0f);
		Vec4 color(1.50f, 1.50f, 1.50f, 1.0f);
		Vec3 pos(1, 1, 1);


		{
			//R2D2 with texture
			Vec4 White(1.0f, 1.0f, 1.0f, 1.0f);
			GraphicsObject *pGraphicsObj = new GraphicsObject_TextureLight(pR2D2Mesh, pShaderObject_textureLight, Texture::Name::R2D2, White, pos);
			GameObjectBasic *pGameObj = new GameObjectBasic(pGraphicsObj);
			pGameObj->SetScale(90,90,90);
			pGameObj->SetTrans(0.5f, 0.5f, -3.2f);
			Quat q1(Quat::Rot1::Y, -MATH_PI2);
			Quat q2(Quat::Rot1::Z, MATH_PI);
			Quat q = q1 * q2;
			pGameObj->SetQuat(q);
			pGameObj->delta_z = 0.006f;
			GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());
		}
		{
			//R2D2 Wireframe
			GraphicsObject *pGraphicsObj = new GraphicsObject_Wireframe(pR2D2Mesh, pShaderObject_colorSingle);

			GameObjectBasic *pGameObj = new GameObjectBasic(pGraphicsObj);
			pGameObj->SetScale(90,90,90);
			pGameObj->SetTrans(0.5f, 0.5f, 3.5f);
			Quat q1(Quat::Rot1::Y, -MATH_PI2);
			Quat q2(Quat::Rot1::Z, MATH_PI);
			Quat q = q1 * q2;
			pGameObj->SetQuat(q);
			pGameObj->delta_z= 0.006f;

			GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());
		}
		{
			GraphicsObject *pGraphicsObj = new GraphicsObject_TextureLight(pWoodCrateMesh, pShaderObject_textureLight, Texture::Name::CRATE, color, pos);
			GameObjectBasic *pGameObj = new GameObjectBasic(pGraphicsObj);
			pGameObj->delta_y = .003f;
			pGameObj->delta_z = .003f;
			pGameObj->SetScale(0.6f, 0.6f, 0.6f);
			pGameObj->SetTrans(-2.5f, 1.0f, -3.0f);
			Quat q1(Quat::Rot1::Y, -MATH_PI2);
			Quat q2(Quat::Rot1::Z, MATH_PI);
			Quat q = q1 * q2;
			pGameObj->SetQuat(q);

			GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());
		}
		{
			//Space Frigate

			GraphicsObject *pGraphicsObj = new GraphicsObject_TextureLight(pSpaceFrigateMesh, pShaderObject_textureLight, Texture::Name::SPACE_FRIGATE, color, pos);
			GameObjectBasic *pGameObj = new GameObjectBasic(pGraphicsObj);
			pGameObj->delta_y = .007f;
			pGameObj->delta_z = .005f;
			pGameObj->SetScale(0.03f, 0.03f, 0.03f);
			pGameObj->SetTrans(-2.5f, 1.0f, 3.0f);
			Quat q1(Quat::Rot1::Y, -MATH_PI2);
			Quat q2(Quat::Rot1::Z, MATH_PI);
			Quat q = q1 * q2;
			pGameObj->SetQuat(q);

			GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());
		}

		// --------------------------------------------
		// Sprite
		// --------------------------------------------

		GraphicsObject_Sprite* pGraphics_Sprite = new GraphicsObject_Sprite(pSpriteMesh, pShaderObject_sprite, pImageGreen, Rect(700, 150, 130, 130));
		GameObject2D* pA1 = new GameObject2D(pGraphics_Sprite);
		GameObjectMan::Add(pA1, GameObjectMan::GetRoot());

		pA1->SetName("ALIEN1");

		GraphicsObject_Sprite* pGraphics_Sprite2 = new GraphicsObject_Sprite(pSpriteMesh, pShaderObject_sprite, pImageRed, Rect(500, 150, 130, 130));
		GameObject2D* pA2 = new GameObject2D(pGraphics_Sprite2);
		GameObjectMan::Add(pA2, GameObjectMan::GetRoot());

		pA2->SetName("ALIEN2");

		//Load all anims to manager
		{
			//---------------------------------------
			// Mousey - All Anims
			//---------------------------------------

			// Grab Mouse clip1
			Clip* pClip = new Clip("Data\\Joyful Jump.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_JUMP, pClip);

			// Grab Mouse clip2
			pClip = new Clip("Data\\Mousey_Gangnam_Style.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_GANGNAM, pClip);

			// Grab Mouse clip3
			pClip = new Clip("Data\\Mousey_Happy_Walk.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_HAPPY_WALK, pClip);

			// Grab Mouse clip4
			pClip = new Clip("Data\\Mousey_Hip_Hop_Dancing.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_HIP_HOP, pClip);

			// Grab Mouse clip5
			pClip = new Clip("Data\\Mousey_Northern_Soul_Spin2.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_NORTH_SOUL, pClip);

			// Grab Mouse clip6
			pClip = new Clip("Data\\Mousey_Rumba_Dancing.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_RUMBA, pClip);

			// Grab Mouse clip7
			pClip = new Clip("Data\\Mousey_Run_Forward.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_RUN, pClip);

			// Grab Mouse clip8
			pClip = new Clip("Data\\Mousey_Run_Forward.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_RUN, pClip);

			// Grab Mouse clip8
			pClip = new Clip("Data\\Mousey_Shuffling.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::MOUSE_SHUFFLE, pClip);

			//---------------------------------------
			// Chickeny - All Anims
			//---------------------------------------

			// Grab Chicken clip1
			pClip = new Clip("Data\\walk_mesh.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::CHICKEN_WALK, pClip);

			// Grab Chicken clip2
			pClip = new Clip("Data\\shot_up+mesh.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::CHICKEN_SHOT_UP, pClip);

			// Grab Chicken clip3
			pClip = new Clip("Data\\sidestep_right+mesh.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::CHICKEN_SIDE_STEP_R, pClip);

			// Grab Chicken clip4
			pClip = new Clip("Data\\run+mesh.a.proto.azul");
			assert(pClip);

			AnimMan::Add(Anim::Name::CHICKEN_RUN, pClip);
		}
		//Load 5 mouse animations
		{
			//---------------------------------------
			// Mouse - GameObject load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("Mouse.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::MOUSEY_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::MOUSEY);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(1, 1, 1);
			pGameSkin->SetTrans(1, 0, -1.25);

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("MouseSkin");
			//---------------------------------------
			// Mousey - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pMouseMixer = new Mixer(AnimMan::Find(Anim::Name::MOUSE_JUMP));
			assert(pMouseMixer);

			pGameSkin->SetMixer(pMouseMixer);

			// Anim controller
			pMouseAnimController = new AnimController(0.250f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::MOUSE_JUMP));
			assert(pMouseAnimController);

			pGameSkin->SetAnimController(pMouseAnimController);

			// holds sbo: local,hierarchy,world, invBind
			pMouseWorldCompute = new WorldCompute(pMouseMixer, "Data\\Mouse.h.proto.azul", "Data\\Mouse.i.proto.azul");

			pGameSkin->SetWorldCompute(pMouseWorldCompute);
			pGraphicsSkin->SetWorldCompute(pMouseWorldCompute);
		}
		{
			//---------------------------------------
			// Mouse - GameObject load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("Mouse.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::MOUSEY_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::MOUSEY);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(1, 1, 1);
			pGameSkin->SetTrans(1, 0, 0);

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("MouseSkin");
			//---------------------------------------
			// Mousey - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pMouseMixer2 = new Mixer(AnimMan::Find(Anim::Name::MOUSE_GANGNAM));
			assert(pMouseMixer2);

			pGameSkin->SetMixer(pMouseMixer2);

			// Anim controller
			pMouseAnimController2 = new AnimController(0.250f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::MOUSE_GANGNAM));
			assert(pMouseAnimController2);

			pGameSkin->SetAnimController(pMouseAnimController2);

			// holds sbo: local,hierarchy,world, invBind
			pMouseWorldCompute = new WorldCompute(pMouseMixer2, "Data\\Mouse.h.proto.azul", "Data\\Mouse.i.proto.azul");

			pGameSkin->SetWorldCompute(pMouseWorldCompute);
			pGraphicsSkin->SetWorldCompute(pMouseWorldCompute);
		}
		{
			//---------------------------------------
			// Mouse - GameObject load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("Mouse.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::MOUSEY_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::MOUSEY);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(1, 1, 1);
			pGameSkin->SetTrans(1, 0, 1.25);

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("MouseSkin");
			//---------------------------------------
			// Mousey - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pMouseMixer3 = new Mixer(AnimMan::Find(Anim::Name::MOUSE_HAPPY_WALK));
			assert(pMouseMixer3);

			pGameSkin->SetMixer(pMouseMixer3);

			// Anim controller
			pMouseAnimController3 = new AnimController(0.250f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::MOUSE_HAPPY_WALK));
			assert(pMouseAnimController3);

			pGameSkin->SetAnimController(pMouseAnimController3);

			// holds sbo: local,hierarchy,world, invBind
			pMouseWorldCompute = new WorldCompute(pMouseMixer3, "Data\\Mouse.h.proto.azul", "Data\\Mouse.i.proto.azul");

			pGameSkin->SetWorldCompute(pMouseWorldCompute);
			pGraphicsSkin->SetWorldCompute(pMouseWorldCompute);
		}
		{
			//---------------------------------------
			// Mouse - GameObject load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("Mouse.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::MOUSEY_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::MOUSEY);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(1, 1, 1);
			pGameSkin->SetTrans(-1, 0, 0);

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("MouseSkin");
			//---------------------------------------
			// Mousey - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pMouseMixer4 = new Mixer(AnimMan::Find(Anim::Name::MOUSE_HIP_HOP));
			assert(pMouseMixer4);

			pGameSkin->SetMixer(pMouseMixer4);

			// Anim controller
			pMouseAnimController4 = new AnimController(0.250f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::MOUSE_HIP_HOP));
			assert(pMouseAnimController4);

			pGameSkin->SetAnimController(pMouseAnimController4);

			// holds sbo: local,hierarchy,world, invBind
			pMouseWorldCompute = new WorldCompute(pMouseMixer4, "Data\\Mouse.h.proto.azul", "Data\\Mouse.i.proto.azul");

			pGameSkin->SetWorldCompute(pMouseWorldCompute);
			pGraphicsSkin->SetWorldCompute(pMouseWorldCompute);
		}
		{
			//---------------------------------------
			// Mouse - GameObject load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("Mouse.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::MOUSEY_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::MOUSEY);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(1, 1, 1);
			pGameSkin->SetTrans(-1, 0, -1.25);

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("MouseSkin");
			//---------------------------------------
			// Mousey - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pMouseMixer5 = new Mixer(AnimMan::Find(Anim::Name::MOUSE_RUMBA));
			assert(pMouseMixer5);

			pGameSkin->SetMixer(pMouseMixer5);

			// Anim controller
			pMouseAnimController5 = new AnimController(0.250f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::MOUSE_RUMBA));
			assert(pMouseAnimController5);

			pGameSkin->SetAnimController(pMouseAnimController5);

			// holds sbo: local,hierarchy,world, invBind
			pMouseWorldCompute = new WorldCompute(pMouseMixer5, "Data\\Mouse.h.proto.azul", "Data\\Mouse.i.proto.azul");

			pGameSkin->SetWorldCompute(pMouseWorldCompute);
			pGraphicsSkin->SetWorldCompute(pMouseWorldCompute);
		}
		//Below loads 4 chicken anim managers
		{
			//---------------------------------------
			// Chicken - GameObject load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("ChickenBot.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::CHICKEN_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::CHICKEN_BOT);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(40, 40, 40);
			pGameSkin->SetTrans(-3, 0, -1);

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("ChickenSkin");
			//---------------------------------------
			// Chickeny - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pChickenMixer = new Mixer(AnimMan::Find(Anim::Name::CHICKEN_WALK));
			assert(pChickenMixer);

			pGameSkin->SetMixer(pChickenMixer);

			// Anim controller
			pChickenAnimController = new AnimController(0.250f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::CHICKEN_WALK));
			assert(pChickenAnimController);

			pGameSkin->SetAnimController(pChickenAnimController);

			// holds sbo: local,hierarchy,world, invBind
			pChickenWorldCompute = new WorldCompute(pChickenMixer, "Data\\ChickenBot.h.proto.azul", "Data\\ChickenBot.i.proto.azul");

			pGameSkin->SetWorldCompute(pChickenWorldCompute);
			pGraphicsSkin->SetWorldCompute(pChickenWorldCompute);
		}
		{
			//---------------------------------------
			// Chicken - GameObject2 load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("ChickenBot.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::CHICKEN_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::CHICKEN_BOT);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(40, 40, 40);
			pGameSkin->SetTrans(-3, 0, 0.5);

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("ChickenSkin");
			//---------------------------------------
			// Chickeny - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pChickenMixer2 = new Mixer(AnimMan::Find(Anim::Name::CHICKEN_SHOT_UP));
			assert(pChickenMixer2);

			pGameSkin->SetMixer(pChickenMixer2);

			// Anim controller
			pChickenAnimController2 = new AnimController(0.250f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::CHICKEN_SHOT_UP));
			assert(pChickenAnimController2);

			pGameSkin->SetAnimController(pChickenAnimController2);

			// holds sbo: local,hierarchy,world, invBind
			pChickenWorldCompute = new WorldCompute(pChickenMixer2, "Data\\ChickenBot.h.proto.azul", "Data\\ChickenBot.i.proto.azul");

			pGameSkin->SetWorldCompute(pChickenWorldCompute);
			pGraphicsSkin->SetWorldCompute(pChickenWorldCompute);
		}
		{
			//---------------------------------------
			// Chicken - GameObject3 load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("ChickenBot.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::CHICKEN_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::CHICKEN_BOT);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(40, 40, 40);
			pGameSkin->SetTrans(-1.25, 0, 1.5);
			//pGameSkin->cur_rot_x = 1.0f;

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("ChickenSkin");
			//---------------------------------------
			// Chickeny - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pChickenMixer3 = new Mixer(AnimMan::Find(Anim::Name::CHICKEN_SIDE_STEP_R));
			assert(pChickenMixer3);

			pGameSkin->SetMixer(pChickenMixer3);

			// Anim controller
			pChickenAnimController3 = new AnimController(0.350f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::CHICKEN_SIDE_STEP_R));
			assert(pChickenAnimController3);

			pGameSkin->SetAnimController(pChickenAnimController3);

			// holds sbo: local,hierarchy,world, invBind
			pChickenWorldCompute = new WorldCompute(pChickenMixer3, "Data\\ChickenBot.h.proto.azul", "Data\\ChickenBot.i.proto.azul");

			pGameSkin->SetWorldCompute(pChickenWorldCompute);
			pGraphicsSkin->SetWorldCompute(pChickenWorldCompute);
		}
		{
			//---------------------------------------
			// Chicken - GameObject4 load
			//---------------------------------------

			Mesh* pSkinMesh = new ProtoMesh("ChickenBot.m.proto.azul");
			MeshNodeMan::Add(Mesh::Name::CHICKEN_SKIN, pSkinMesh);

			GraphicsObject_SkinTexture* pGraphicsSkin = new GraphicsObject_SkinTexture(pSkinMesh, pShaderObject_SkinTexture, Texture::Name::CHICKEN_BOT);
			GameObjectAnimSkin* pGameSkin = new GameObjectAnimSkin(pGraphicsSkin);

			pGameSkin->delta_y = 0.00f;
			pGameSkin->SetScale(40, 40, 40);
			pGameSkin->SetTrans(-3, 0, 1.5);
			//pGameSkin->cur_rot_x = 1.0f;

			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());
			pGameSkin->SetName("ChickenSkin");
			//---------------------------------------
			// Chickeny - Mixer
			//---------------------------------------

			// Create a mixer (holds keyA,keyB,tS,result)
			pChickenMixer4 = new Mixer(AnimMan::Find(Anim::Name::CHICKEN_RUN));
			assert(pChickenMixer4);

			pGameSkin->SetMixer(pChickenMixer4);

			// Anim controller
			pChickenAnimController4 = new AnimController(0.450f * AnimTime(AnimTime::Duration::FILM_24_FRAME), AnimMan::Find(Anim::Name::CHICKEN_RUN));
			assert(pChickenAnimController4);

			pGameSkin->SetAnimController(pChickenAnimController4);

			// holds sbo: local,hierarchy,world, invBind
			pChickenWorldCompute = new WorldCompute(pChickenMixer4, "Data\\ChickenBot.h.proto.azul", "Data\\ChickenBot.i.proto.azul");

			pGameSkin->SetWorldCompute(pChickenWorldCompute);
			pGraphicsSkin->SetWorldCompute(pChickenWorldCompute);
		}
	}

	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------
	void Game::Update(float )
	{
		// ------------------------------------
		// Camera update
		// ------------------------------------

		Camera3D *pCam3D = CameraMan::GetCurrent3D();
		pCam3D->updateCamera();

		Camera2D *pCam2D = CameraMan::GetCurrent2D();
		pCam2D->updateCamera();

		// ------------------------------------------------
		// Timer update
		// ------------------------------------------------

		this->intervalTimer.Toc(); 
		this->intervalTimer.Tic(); 

		// ------------------------------------
		// Animate Me
		// ------------------------------------
		
		pMouseAnimController->Update(pMouseMixer);
		pMouseAnimController2->Update(pMouseMixer2);
		pMouseAnimController3->Update(pMouseMixer3);
		pMouseAnimController4->Update(pMouseMixer4);
		pMouseAnimController5->Update(pMouseMixer5);
		pChickenAnimController->Update(pChickenMixer);
		pChickenAnimController2->Update(pChickenMixer2);
		pChickenAnimController3->Update(pChickenMixer3);
		pChickenAnimController4->Update(pChickenMixer4);

		if (myKeyboard.GetKeyState(Keyboard::Key::KEY_1))
		{
			pMouseAnimController->SetAnim(AnimMan::Find(Anim::Name::MOUSE_HAPPY_WALK));
			pMouseAnimController2->SetAnim(AnimMan::Find(Anim::Name::MOUSE_NORTH_SOUL));
			pMouseAnimController3->SetAnim(AnimMan::Find(Anim::Name::MOUSE_RUN));
			pMouseAnimController4->SetAnim(AnimMan::Find(Anim::Name::MOUSE_JUMP));
			pMouseAnimController5->SetAnim(AnimMan::Find(Anim::Name::MOUSE_GANGNAM));
		}
		if (myKeyboard.GetKeyState(Keyboard::Key::KEY_2))
		{
			pMouseAnimController->SetAnim(AnimMan::Find(Anim::Name::MOUSE_JUMP));
			pMouseAnimController2->SetAnim(AnimMan::Find(Anim::Name::MOUSE_GANGNAM));
			pMouseAnimController3->SetAnim(AnimMan::Find(Anim::Name::MOUSE_HAPPY_WALK));
			pMouseAnimController4->SetAnim(AnimMan::Find(Anim::Name::MOUSE_HIP_HOP));
			pMouseAnimController5->SetAnim(AnimMan::Find(Anim::Name::MOUSE_RUMBA));
		}
		if (myKeyboard.GetKeyState(Keyboard::Key::KEY_3))
		{
			pChickenAnimController->SetAnim(AnimMan::Find(Anim::Name::CHICKEN_RUN));
			pChickenAnimController2->SetAnim(AnimMan::Find(Anim::Name::CHICKEN_WALK));
			pChickenAnimController3->SetAnim(AnimMan::Find(Anim::Name::CHICKEN_SHOT_UP));
			pChickenAnimController4->SetAnim(AnimMan::Find(Anim::Name::CHICKEN_WALK));
		}
		if (myKeyboard.GetKeyState(Keyboard::Key::KEY_4))
		{
			pChickenAnimController->SetAnim(AnimMan::Find(Anim::Name::CHICKEN_WALK));
			pChickenAnimController2->SetAnim(AnimMan::Find(Anim::Name::CHICKEN_SHOT_UP));
			pChickenAnimController3->SetAnim(AnimMan::Find(Anim::Name::CHICKEN_SIDE_STEP_R));
			pChickenAnimController4->SetAnim(AnimMan::Find(Anim::Name::CHICKEN_RUN));			
		}

		// ------------------------------------
		// Update GameObjects
		// ------------------------------------
		GameObjectMan::Update(this->globalTimer.Toc());
	}


	//-----------------------------------------------------------------------------
	// Game::Draw()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//-----------------------------------------------------------------------------
	void Game::Draw()
	{
		GameObjectMan::Draw();
	}


	//-----------------------------------------------------------------------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//-----------------------------------------------------------------------------
	void Game::UnLoadContent()
	{
		TextureMan::Destroy();
		InputMan::Destroy();
		GameObjectMan::Destroy();
		MeshNodeMan::Destroy();
		ShaderMan::Destroy();
		CameraMan::Destroy();
		ImageMan::Destroy();

		delete pMouseAnimController;
		delete pMouseAnimController2;
		delete pMouseAnimController3;
		delete pMouseAnimController4;
		delete pMouseAnimController5;
		delete pMouseMixer;
		delete pMouseMixer2;
		delete pMouseMixer3;
		delete pMouseMixer4;
		delete pMouseMixer5;
		delete pMouseWorldCompute;

		delete pChickenAnimController;
		delete pChickenAnimController2;
		delete pChickenAnimController3;
		delete pChickenAnimController4;
		delete pChickenMixer;
		delete pChickenMixer2;
		delete pChickenMixer3;
		delete pChickenMixer4;		
		delete pChickenWorldCompute;
	}

	//------------------------------------------------------------------
	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	//------------------------------------------------------------------
	void Game::ClearBufferFunc()
	{
	#ifdef _DEBUG
		const GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	#else
		const GLfloat color[] = { 0.85f, 0.7f, 0.7f, 1.0f };
	#endif
		const GLfloat one = 1.0f;

		glViewport(0, 0, info.windowWidth, info.windowHeight);
		glClearBufferfv(GL_COLOR, 0, color);
		glClearBufferfv(GL_DEPTH, 0, &one);
	}


	void Game::SetProtoVersion( char * const pVersion)
	{
		assert(pVersion);

		this->pProtoVersion = pVersion;
	}

	const char *const Game::GetProtoVersion()
	{
		return this->pProtoVersion;
	}

}  // namespace 

// --- End of File ---
