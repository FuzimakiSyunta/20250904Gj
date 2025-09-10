#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//背景の画像のデータ取得
	uint32_t textureTitle = TextureManager::Load("Title.png");
	titleButton[0] = TextureManager::Load("TitleButton.png");
	titleButton[1] = TextureManager::Load("mouseOk.png");
	//画像の座標

	//pos = { 640,400 };
	titleSprite = Sprite::Create(textureTitle, pos, { 1,1,1,1 } );
	titleButtonSprite[2] = Sprite::Create(titleButton[2], {0,0}, {1,1,1,1});

	pos = { 640,400 };
	titleSprite = Sprite::Create(textureTitle, pos, { 1,1,1,1 }, { 0.5f,0.5f });
	titleButtonSprite[0] = Sprite::Create(titleButton[0], {0,0}, {1,1,1,1}, {0.0f,0.0f});
	titleButtonSprite[1] = Sprite::Create(titleButton[1], { 0,0 }, { 1,1,1,1 }, { 0.0f,0.0f });

	isSceneEnd_ = false;

	color = { 0,0,0,0 };

	fadeInTexture = TextureManager::Load("uvChecker.png");
	fadeInSprite.reset(Sprite::Create(fadeInTexture, { 640,370 }, color, { 0.5f,0.5f }));

	fadeInSprite->SetSize({1280,820});
	//すぐにシーンに移らないためのクールタイム初期化
	sceneCooltime = 0;

	fadeColor = 0.01f;
}

void TitleScene::Update()
{
	//すぐにシーンに移らないようにする処理
	if (isSceneEnd_ == false)
	{
		sceneCooltime++;
	}

	//マウスの座標を取得
	GetCursorPos(&mousePosition); 
	HWND hwnd = WinApp::GetInstance()->GetHwnd(); 
	ScreenToClient(hwnd, &mousePosition);
	//--------------------//
	
	//ボタンやクリックをしたら次のシーンに行くための処理
	if (input_->PushKey(DIK_SPACE)&&  sceneCooltime > 10||
		mousePosition.x >= 80 && mousePosition.x <= 366 && mousePosition.y >= 370 && mousePosition.y <= 500 && input_->IsPressMouse(WM_LBUTTONDOWN == 0) && sceneCooltime > 10)
	{
		isFade = true;
	}

	if (isFade==true)
	{
		color.w += fadeColor;
		fadeInSprite->SetColor(color);
	}

	if (color.w >= 1)
	{
		isFade = false;
		isSceneEnd_ = true;
	}

}

void TitleScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	titleSprite->Draw();
	titleButtonSprite[0]->Draw();
	titleButtonSprite[1]->Draw();

	fadeInSprite->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void TitleScene::Reset()
{
	Initialize();
}