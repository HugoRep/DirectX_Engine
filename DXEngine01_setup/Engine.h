#pragma once
#include "DxApp.h"
class Engine : public DxApp
{
public:
	Engine(HINSTANCE hinstance);
	virtual ~Engine();

	int Run();
	bool Init() override;
	void Update() override;
	void Render() override;
};