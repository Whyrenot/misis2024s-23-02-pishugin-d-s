#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <strstream>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <thread>
#define PI 3.14159265359
double HEIGHT = 800;
double WIDTH = 800;
double FIELD_OF_VIEW = 90;
#define Z_FAR 10000
#define Z_NEAR 0.1


class Matrix {
public:
	std::vector<std::vector<double>> v;
public:
	Matrix() : v(std::vector<std::vector<double>>(4, std::vector<double>(1, 0))) {}
	Matrix(const std::vector<std::vector<double>>& vec) : v(vec) {}
	Matrix(const Matrix& m) = default;
	Matrix(Matrix&& m) noexcept = default;
	Matrix(std::vector<std::vector<double>>&& vec) : v(vec) {}
	virtual void print() {
		for (auto row : v) {
			for (auto col : row) {
				std::cout << col << " ";
			}
			std::cout << "\n";
		}
	}
	std::vector<double>& operator[](int i) {
		return v[i];
	}
	Matrix& operator=(const Matrix& m) = default;
	Matrix& operator=(Matrix&& m) noexcept = default;
	Matrix& operator=(const std::vector<std::vector<double>>& vec) {
		v = vec;
	}
	Matrix operator * (const Matrix& m) {
		if (v[0].size() == m.v.size()) {
			std::vector<std::vector<double>> c(v.size(), std::vector<double>(m.v[0].size(), 0));
			for (int row = 0; row < v.size(); row++) { // перебор по строкам первой матриц
				for (int col = 0; col < m.v[0].size(); col++) {  // перебор по столбцам второй матрицы
					for (int inner = 0; inner < m.v.size(); inner++) { // перебор одновременно по столбцу первой матрицы и строкам второй
						/*c.at(row).at(col) += v.at(row).at(inner) * m.v.at(inner).at(col);*/ c[row][col] += v[row][inner] * m.v[inner][col];
					}
				}
			}
			return Matrix(c);
		}
		else {
			std::cout << "Impossible\n";
		}
	}
	Matrix& operator *= (const Matrix& m) {
		*this = (*this * m);
		return *this;
	}
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	Matrix matrix(lhs);
	return matrix *= rhs;
}

Matrix operator*(Matrix&& lhs, const Matrix& rhs) {
	return lhs *= rhs;
}

Matrix operator*(const Matrix& lhs, Matrix&& rhs) {
	Matrix matrix(lhs);
	return matrix *= rhs;
}

Matrix operator*(Matrix&& lhs, Matrix&& rhs) {
	return lhs *= rhs;
}


class Vec3d : public Matrix {
public:
	Vec3d() : Matrix() {}
	Vec3d(const std::vector<std::vector<double>>& v) : Matrix(v) {}
	Vec3d(std::vector<std::vector<double>>&& v) : Matrix(v) {}
	Vec3d(const Matrix& m) : Matrix(m) {}
	Vec3d(double x, double y, double z, double w = 1) {
		v[0][0] = x, v[1][0] = y, v[2][0] = z, v[3][0] = w;
	}
	Vec3d& operator=(const Vec3d& m) {
		v = m.v;
		return *this;
	}
	void print() override {
		std::cout << v[0][0] << " " << v[1][0]<< " " << v[2][0] << " " << v[3][0] << "\n";
	}
};

double vec_dot_product(const Vec3d& v1, const Vec3d& v2) {
	return v1.v[0][0] * v2.v[0][0] + v1.v[1][0] * v2.v[1][0] + v1.v[2][0] * v2.v[2][0];
}

Vec3d vec_cross_product(const Vec3d& v1, const Vec3d& v2) {
	return Vec3d(v1.v[1][0] * v2.v[2][0] - v2.v[1][0] * v1.v[2][0], -(v1.v[0][0] * v2.v[2][0] - v1.v[2][0] * v2.v[0][0]), v1.v[0][0] * v2.v[1][0] - v1.v[1][0] * v2.v[0][0]);
}

class Polygon {
public:
	Vec3d *vertex1, *vertex2, *vertex3;
	sf::Color color;

	Polygon(Vec3d &vertex1, Vec3d &vertex2, Vec3d &vertex3, const sf::Color& color) {
		this->vertex1 = &vertex1, this->vertex2 = &vertex2, this->vertex3 = &vertex3, this->color = color;
	}
};

class Mesh {
protected:
	std::vector<Polygon> polygon_array;
	std::vector<Vec3d> verts;
	std::vector<Vec3d> transformed_verts;
	Vec3d position;
	double scale;
	double angle_x = 0, angle_z = 0;
	Matrix p, t, a, b;
public:
	Mesh(const Vec3d& position, const double scale) {
		this->position = position;
		this->scale = scale;
	}
	void LoadFromFile(const std::string& name) {

		std::ifstream f(name);
		if (!f.is_open())
			std::cout << "ERROR READING MESH FILE\n";
		else {
			while (!f.eof()) {
				char line[128];
				f.getline(line, 128);

				std::strstream s;
				s << line;

				char junk;

				if (line[0] == 'v')
				{
					double x, y, z;
					s >> junk >> x >> y >> z;
					Vec3d v(x, y, z);
					verts.push_back(v);
					transformed_verts.push_back(v);
				}

				if (line[0] == 'f')
				{
					int f[3];
					s >> junk >> f[0] >> f[1] >> f[2];
					int r = rand() % 100;
					polygon_array.push_back(Polygon(transformed_verts[f[0] - 1], transformed_verts[f[1] - 1], transformed_verts[f[2] - 1], sf::Color(75 + r, 100 + r, 100 + r)));
				}
			}
		}
	}
	void update() {
		//Move origin

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			position.v[1][0] += 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			position.v[1][0] -= 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			position.v[0][0] += 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			position.v[0][0] -= 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			position.v[2][0] += 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			position.v[2][0] -= 0.1;
		}


		//Rotation
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			angle_z += 0.7;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			angle_z -= 0.7;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			angle_x += 0.7;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			angle_x -= 0.7;
		}

		p = Matrix({
			{ (WIDTH / HEIGHT) / (std::tan((FIELD_OF_VIEW / 2) * PI / 180)),0,0,0},
			{ 0, 1 / (std::tan((FIELD_OF_VIEW / 2) * PI / 180)),0,0},
			{ 0,0,Z_FAR / (Z_FAR - Z_NEAR),-Z_FAR * Z_NEAR / (Z_FAR - Z_NEAR) },   // 1 / (std::tan(FIELD_OF_VIEW / 2 * PI / 180))
			{ 0,0,1,0 },
		});

		t = Matrix({
			{1,0,0,position.v[0][0]}, // ВОТ ТУТ бЫЛА ОШИБКА
			{0,1,0,position.v[1][0]},
			{0,0,1,position.v[2][0]},
			{0,0,0,1},
		});

		a = Matrix({
			{1,0,0,0},
			{0, std::cos(angle_x * PI / 180),-std::sin(angle_x * PI / 180),0},
			{0, std::sin(angle_x * PI / 180),std::cos(angle_x * PI / 180),0},
			{0,0,0,1}
		});

		b = Matrix({
			{std::cos(angle_z * PI / 180),0,std::sin(angle_z * PI / 180),0},
			{0, 1,0,0},
			{-std::sin(angle_z * PI / 180), 0,std::cos(angle_z * PI / 180),0},
			{0,0,0,1}
		});

		for (int i = 0; i < verts.size(); i++) {
			Matrix mat(t);
			mat *= a;
			mat *= b;
			mat *= verts[i];
			transformed_verts[i] = std::move(mat);
		}
	}
	void draw(sf::RenderWindow& window) {

		std::vector<sf::VertexArray> tris;
		std::vector<sf::Vector2f> z_buffer;

		int index = 0;

		for (auto& el : polygon_array) {

			sf::VertexArray tri(sf::Triangles, 3);
			
			// cross product of 2 vectors
			Vec3d v1v2((*el.vertex2).v[0][0] - (*el.vertex1).v[0][0], (*el.vertex2).v[1][0] - (*el.vertex1).v[1][0], (*el.vertex2).v[2][0] - (*el.vertex1).v[2][0]);
			Vec3d v1v3((*el.vertex3).v[0][0] - (*el.vertex1).v[0][0], (*el.vertex3).v[1][0] - (*el.vertex1).v[1][0], (*el.vertex3).v[2][0] - (*el.vertex1).v[2][0]);
			Vec3d normal = vec_cross_product(v1v2, v1v3);
			Vec3d camera_normal = Vec3d(((*el.vertex1).v[0][0] + (*el.vertex2).v[0][0] + (*el.vertex3).v[0][0]) / 3, ((*el.vertex1).v[1][0] + (*el.vertex2).v[1][0] + (*el.vertex3).v[1][0]) / 3, ((*el.vertex1).v[2][0] + (*el.vertex2).v[2][0] + (*el.vertex3).v[2][0]) / 3);



			if (vec_dot_product(normal, camera_normal) <= 0) {

				tri[0].color = el.color;
				tri[1].color = el.color;
				tri[2].color = el.color;

				Vec3d v1 = p * (*el.vertex1); 
				if (v1.v[3][0] != 0) {
					v1.v[0][0] /= v1.v[3][0];
					v1.v[1][0] /= v1.v[3][0];
					v1.v[2][0] /= v1.v[3][0];
				}

				Vec3d v2 = p * (*el.vertex2);
				if (v2.v[3][0] != 0) {
					v2.v[0][0] /= v2.v[3][0];
					v2.v[1][0] /= v2.v[3][0];
					v2.v[2][0] /= v2.v[3][0];
				}

				Vec3d v3 = p * (*el.vertex3);
				if (v3.v[3][0] != 0) {
					v3.v[0][0] /= v3.v[3][0];
					v3.v[1][0] /= v3.v[3][0];
					v3.v[2][0] /= v3.v[3][0];
				}

				tri[0].position = sf::Vector2f(v1.v[0][0] * scale + WIDTH / 2, v1.v[1][0] * scale + HEIGHT / 2);
				tri[1].position = sf::Vector2f(v2.v[0][0] * scale + WIDTH / 2, v2.v[1][0] * scale + HEIGHT / 2);
				tri[2].position = sf::Vector2f(v3.v[0][0] * scale + WIDTH / 2, v3.v[1][0] * scale + HEIGHT / 2);

			
				tris.push_back(tri);
				z_buffer.push_back(sf::Vector2f((v1.v[2][0] + v2.v[2][0] + v3.v[2][0]) / 3, index));
				index++;
			}
			
		}
		
		std::sort(z_buffer.begin(), z_buffer.end(), [](sf::Vector2f& a, sf::Vector2f& b) {
			return a.x > b.x;
		});

		for (int i = 0; i < z_buffer.size(); i++)
		{
			window.draw(tris[z_buffer[i].y]);
		}
	}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML");
	//window.setFramerateLimit(30);

	Mesh c(Vec3d(0, 0, 3), 300);
	c.LoadFromFile("resources/1untitled.obj");

	//////
	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	//////
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			}
		}

		c.update();


		window.clear();
		c.draw(window);
		window.display();
		//window.close();


		///////
		currentTime = clock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
		std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
		previousTime = currentTime;
		/////////


	}

	return 0;
}
