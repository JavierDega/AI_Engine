
//Analyzes input and modifies scene accordingly (UI_BUTTONS, character control where allowed are main forms of interaction)
//Remember, underlying Keyboard and Mouse DXTK classes are also Singletons
class Input
{
private:
	/*Here will be the instance stored*/
	static Input* m_instance;
	/*Private constructor to prevent instancing*/
	Input(void);
public:
	~Input();
	//Game events
	void Initialize(HWND window);
	void UpdateInput(ID3D11Device1 * device);
	void Reset();
	//Singleton
	static Input* GetInstance();
	//Variables
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;
	//Mouse tracker (Pressed, Released)
	DirectX::Mouse::ButtonStateTracker m_tracker;

};
