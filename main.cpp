#include <Novice.h>
#include <imgui.h>
#include "algorithm"
#include "Calculation.h"

const char kWindowTitle[] = "LE2A_13_ホリケ_ハヤト_確認課題04_03";

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
	Vector3 translate{ 0.0f, -5.0f, 15.0f };

	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };

	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 viewProjectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;

	float deltaTime = 1.0f / 60.0f;

	// ボブ
	Ball ball;
	ball.position = { 5.0f, 10.0f, 0.0f };
	ball.velocity = { 0.0f, 0.0f, 0.0f };
	ball.acceleration = { 0.0f, -9.8f, 0.0f };
	ball.mass = 1.0f;
	ball.radius = 0.5f;
	ball.color = 0xFFFFFFFF;

	// 平面
	Plane plane = { { 0.0f, 1.0f, 0.0f }, 1.0f };

	// 係数
	float e = 0.7f;

	bool isStart = false;

	// 今と前の位置を入手する
	Vector3 P0 = {};
	Vector3 P1 = {};

	unsigned int color;

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

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			isStart = true;
		}


		// 1フレーム前の位置を保管しておく
		P0 = ball.position;

		color = 0xFFFFFFFF;

		// 円錐振り子運動
		if (isStart) {

			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;

			// 今のフレームの位置を保管しておく
			P1 = ball.position;

			if (IsCollision(Sphere{ ball.position, ball.radius }, plane)) {

				color = 0xFF0000FF;

				float distance0 = Dot(plane.normal, P0) - plane.distance;  // 前フレーム
				float distance1 = Dot(plane.normal, P1) - plane.distance;  // 今フレーム

				// 押し戻し処理
				float t = (ball.radius - distance0) / (distance1 - distance0);
				t = std::clamp(t, 0.0f, 1.0f);
				Vector3 contactPos = Lerp(P0, P1, t);
				ball.position = contactPos;

				// ボールの反射
				Vector3 reflected = Reflect(ball.velocity, plane.normal);
				Vector3 projectToNormal = Project(reflected, plane.normal);
				Vector3 movingDirection = reflected - projectToNormal;
				ball.velocity = projectToNormal * e + movingDirection;

			}
		}
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

		ImGui::DragFloat3("Ball.position", &ball.position.x, 0.1f);
		ImGui::DragFloat3("Plane.normal", &plane.normal.x, 0.1f);
		ImGui::DragFloat("Plane.distance", &plane.distance, 0.1f);
		ImGui::DragFloat("e", &e, 0.01f);

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrowGrid(worldViewProjectionMatrix, viewportMatrix);

		// 平面の描画
		DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, color);

		// 球を描画する
		DrawSphere(Sphere(ball.position, ball.radius), worldViewProjectionMatrix, viewportMatrix, 0x00FF00FF);

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