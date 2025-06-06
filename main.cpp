#include <Novice.h>
#include <imgui.h>
#include "algorithm"
#include "Calculation.h"

const char kWindowTitle[] = "LE2A_13_ホリケ_ハヤト_確認課題02_08";

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
		ImGui::DragFloat3("controlPoint0", &controlPoints[0].x, 0.1f);
		ImGui::DragFloat3("controlPoint1", &controlPoints[1].x, 0.1f);
		ImGui::DragFloat3("controlPoint2", &controlPoints[2].x, 0.1f);

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrowGrid(worldViewProjectionMatrix, viewportMatrix);

		// ベジェ曲線を描画
		DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], viewProjectionMatrix, viewportMatrix, 0x00FF00FF);

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
