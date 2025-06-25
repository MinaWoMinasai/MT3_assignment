#include <Novice.h>
#include <imgui.h>
#include "algorithm"
#include "Calculation.h"

const char kWindowTitle[] = "LE2A_13_ホリケ_ハヤト_確認課題03_01";

// 画面の大きさ
const float kWindowWidth = 1280.0f;
const float kWindowHeight = 720.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 rotate{ 0.0f, 0.0f, 0.0f };
	Vector3 translate{ 0.0f, -15.0f, 50.0f };

	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };

	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 viewProjectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;

	// ベジェ曲線上の点
	Vector3 controlPoints[3] = {
		{0.8f, 0.58f, 1.0f},
		{1.76f, 1.0f, -0.3f},
		{0.94f, -0.7f, 2.3f},
	};

	// 階層構造
	Vector3 translates[3] = {
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f},
	};

	Vector3 rotates[3] = {
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, -1.4f},
		{0.0f, 0.0f, 0.0f },
	};

	Vector3 scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
	};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		/// 

		worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f,1.0f }, rotate, translate);
		cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		viewMatrix = Inverse(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);
		worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		viewportMatrix = MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);
		viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);

		// ローカルとワールドの階層構造変数を宣言する
		Matrix4x4 local0 = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 world0 = local0;

		Matrix4x4 local1 = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		Matrix4x4 world1 = Multiply(local1, world0);

		Matrix4x4 local2 = MakeAffineMatrix(scales[2], rotates[2], translates[2]);
		Matrix4x4 world2 = Multiply(local2, world1);

		ImGuiIO& io = ImGui::GetIO();
		bool imguiWantsMouse = io.WantCaptureMouse;

		if (!imguiWantsMouse) {
			// マウスホイールで前後移動
			if (io.MouseWheel != 0.0f) {
				float moveSpeed = 1.0f; // 適宜調整
				cameraTranslate.z += io.MouseWheel * moveSpeed;
			}

			// 左ドラッグで見渡す（回転）
			if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
				float rotateSpeed = 0.01f;
				ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
				cameraRotate.y += delta.x * rotateSpeed;
				cameraRotate.x += delta.y * rotateSpeed;
				ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left); // 差分をリセット
			}

			// 中ドラッグで平行移動
			if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle)) {
				float panSpeed = 0.01f;
				ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Middle);
				cameraTranslate.x -= delta.x * panSpeed;
				cameraTranslate.y += delta.y * panSpeed;
				ImGui::ResetMouseDragDelta(ImGuiMouseButton_Middle);
			}
		}

		// === カメラ行列を更新 ===
		cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);

		ImGui::Begin("window");
		ImGui::DragFloat3("localScale0", &scales[0].x, 0.1f);
		ImGui::DragFloat3("localRotate0", &rotates[0].x, 0.1f);
		ImGui::DragFloat3("localTranslate0", &translates[0].x, 0.1f);
		ImGui::DragFloat3("localScale1", &scales[1].x, 0.1f);
		ImGui::DragFloat3("localRotate1", &rotates[1].x, 0.1f);
		ImGui::DragFloat3("localTranslate1", &translates[1].x, 0.1f);
		ImGui::DragFloat3("localScale2", &scales[2].x, 0.1f);
		ImGui::DragFloat3("localRotate2", &rotates[2].x, 0.1f);
		ImGui::DragFloat3("localTranslate2", &translates[2].x, 0.1f);

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrowGrid(worldViewProjectionMatrix, viewportMatrix);

		// 各点のワールド位置
		Vector3 pos0 = Transform({ 0, 0, 0 }, world0);  // 肩の位置
		Vector3 pos1 = Transform({ 0, 0, 0 }, world1);  // 肘の位置（肩の子）
		Vector3 pos2 = Transform({ 0, 0, 0 }, world2);  // 手の位置（肘の子）

		// 三点をスクリーン座標に変換
		Vector3 screenWorldTranslate0 = Transform(Transform(pos0, viewProjectionMatrix), viewportMatrix);
		Vector3 screenWorldTranslate1 = Transform(Transform(pos1, viewProjectionMatrix), viewportMatrix);
		Vector3 screenWorldTranslate2 = Transform(Transform(pos2, viewProjectionMatrix), viewportMatrix);

		// 三点で線を引く
		Novice::DrawLine(
			static_cast<int>(screenWorldTranslate0.x),
			static_cast<int>(screenWorldTranslate0.y),
			static_cast<int>(screenWorldTranslate1.x),
			static_cast<int>(screenWorldTranslate1.y),
			0x11CC11FF
		);
		Novice::DrawLine(
			static_cast<int>(screenWorldTranslate1.x),
			static_cast<int>(screenWorldTranslate1.y),
			static_cast<int>(screenWorldTranslate2.x),
			static_cast<int>(screenWorldTranslate2.y),
			0x11CC11FF
		);

		// 三点に球を描画する
		DrawSphere(Sphere(pos0, 0.01f), viewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(Sphere(pos1, 0.01f), viewProjectionMatrix, viewportMatrix, GREEN);
		DrawSphere(Sphere(pos2, 0.01f), viewProjectionMatrix, viewportMatrix, BLUE);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}