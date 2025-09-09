#include "GameExplanation.h"
GameExplanation::GameExplanation()
{
}

GameExplanation::~GameExplanation()
{
}

void GameExplanation::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//背景の画像のデータ取得
	uint32_t Explanationtexture = TextureManager::Load("operation.png");
	explanationButton = TextureManager::Load("operation_StartButton.png");
	//画像の座標
	pos = { 640,400 };
	explanationSprite = Sprite::Create(Explanationtexture, pos, { 1,1,1,1 }, { 0.5f,0.5f });
	explanationButtonSprite = Sprite::Create(explanationButton, { 0,0 }, { 1,1,1,1 }, { 0.0f,0.0f });
	//すぐにシーンに移らないためのクールタイム初期化
	sceneCooltime = 0;

	isSceneEnd_ = false;
}

void GameExplanation::Update()
{
	//マウスの座標を取得
	GetCursorPos(&mousePosition);
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	//--------------------//
	
	//すぐにシーンに移らないようにする処理
	if (isSceneEnd_ == false)
	{
		sceneCooltime++;
	}
	//ボタンやクリックをしたら次のシーンに行くための処理
	if (input_->PushKey(DIK_SPACE)&&sceneCooltime>10||
		mousePosition.x >= 990 && mousePosition.x <= 1220 && mousePosition.y >= 675 && mousePosition.y <= 760 && input_->IsPressMouse(WM_LBUTTONDOWN == 0)&&sceneCooltime>10)
	{
		isSceneEnd_ = true;
	}
}

void GameExplanation::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	explanationSprite->Draw();
	explanationButtonSprite->Draw();
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

void GameExplanation::Reset()
{
	Initialize();
}