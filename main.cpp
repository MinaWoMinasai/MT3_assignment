#define NOMINMAX
#include <Novice.h>
#include <imgui.h>
#include "algorithm"
#include "Calculation.h"

const char kWindowTitle[] = "LE2A_13_ホリケ_ハヤト_確認課題04_04";

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

	// ボール
	Ball ball;
	ball.position = { 5.0f, 10.0f, 0.0f };
	ball.velocity = { 0.0f, 0.0f, 0.0f };
	ball.acceleration = { 0.0f, -98.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.2f;
	ball.color = 0xFFFFFFFF;

	// 平面
	Plane plane = { Normalize({ -0.2f, 0.9f, -0.3f }), 0.0f };

	// 反発係数
	float e = 0.9f;

	bool isStart = false;

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

		color = 0xFFFFFFFF;

		// ボールの挙動と平面との判定
		if (isStart) {
			// スウィープ判定でトンネリングを防止
			Vector3 from = ball.position;
			Vector3 to = from + ball.velocity * deltaTime;

			Vector3 contactPoint;
			if (SweepSphereToPlane(from, to, ball.radius, plane, contactPoint)) {
				// 位置・速度を補正
				ball.position = contactPoint;

				// 反射処理
				Vector3 normalVel = Project(ball.velocity, plane.normal);
				Vector3 tangentVel = ball.velocity - normalVel;
				ball.velocity = -normalVel * e + tangentVel;
			}

			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;

			// めり込み防止
			if (IsCollision(Sphere{ ball.position, ball.radius }, plane)) {
				color = 0xFF0000FF;

				// 法線方向の距離
				float d = Dot(plane.normal, ball.position) - plane.distance;

				// 押し戻す
				ball.position -= plane.normal * (d - ball.radius);

				// 反射処理
				Vector3 normalVel = Project(ball.velocity, plane.normal);
				Vector3 tangentVel = ball.velocity - normalVel;
				ball.velocity = -normalVel * e + tangentVel;
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
		ImGui::DragFloat3("Ball.velocity", &ball.velocity.x, 0.1f);
		ImGui::DragFloat3("Plane.normal", &plane.normal.x, 0.1f);
		ImGui::DragFloat("Plane.distance", &plane.distance, 0.1f);
		ImGui::DragFloat("e", &e, 0.01f);
		plane.normal = Normalize(plane.normal);
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