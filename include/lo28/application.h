//
// Copyright (C) by Mikolaj Mijakowski (Mitos) 2021, for further legal details see LICENSE.md
//



class Application
{
public:
	Application();
	virtual ~Application();

	void show();

	void setSize(unsigned int width, unsigned int height);
	void setTitle(const std::string& title);
	void setResizable(bool resizable);

protected:
	virtual void paint(GraphicsContext g);

private:

};