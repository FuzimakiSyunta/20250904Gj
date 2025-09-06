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
	uint32_t textureTitle = TextureManager::Load("uvChecker.png");
	//画像の座標
	pos = { 400,400 };
	titleSprite = Sprite::Create(textureTitle, pos, { 1,1,1,1 }, { 0.5f,0.5f });
}

void TitleScene::Update()
{
	//マウスの座標を取得
	GetCursorPos(&mousePosition); 
	HWND hwnd = WinApp::GetInstance()->GetHwnd(); 
	ScreenToClient(hwnd, &mousePosition);
	//--------------------//
	
	//ボタンやクリックをしたら次のシーンに行くための処理
	if (input_->PushKey(DIK_SPACE)||
		mousePosition.x >= 400 && mousePosition.x <= 700 && mousePosition.y >= 200 && mousePosition.y <= 500 && input_->IsPressMouse(WM_LBUTTONDOWN == 0))
	{
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