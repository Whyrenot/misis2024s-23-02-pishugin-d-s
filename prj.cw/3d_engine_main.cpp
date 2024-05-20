#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <strstream>
#include <math.h>
#include <algorithm>
#define PI 3.14159265359
double HEIGHT = 800;
double WIDTH = 800;
double FIELD_OF_VIEW = 90;
#define Z_FAR 10000
#define Z_NEAR 0.1


class Matrix {
protected:
	std::vector<std::vector<double>> v;
public:
	Matrix() {
		v = std::vector<std::vector<double>>(4, std::vector<double>(1, 0));
	}
	Matrix(const std::vector<std::vector<double>> v) {
		this->v = v;
	}
	Matrix(const Matrix& m) {
		this->v = m.v;
	}
	void print() {
		for (auto row : v) {
			for (auto col : row) {
				std::cout << col << " ";
			}
			std::cout << "\n";
		}
	}
	std::vector<double>* operator [](const int i) {

		return &v[i];
	}
	void operator = (const Matrix& m) {
		v = m.v;
	}
	void operator = (const std::vector<std::vector<double>> v) {
		this->v = v;
	}
	Matrix operator * (const Matrix& m) {
		if (v[0].size() == m.v.size()) {
			std::vector<std::vector<double>> c(v.size(), std::vector<double>(m.v[0].size(), 0));
			for (int row = 0; row < v.size(); row++) { // перебор по строкам первой матриц
				for (int col = 0; col < m.v[0].size(); col++) {  // перебор по столбцам второй матрицы
					for (int inner = 0; inner < m.v.size(); inner++) { // перебор одновременно по столбцу первой матрицы и строкам второй
						c.at(row).at(col) += v.at(row).at(inner) * m.v.at(inner).at(col);
					}
				}
			}
			return Matrix(c);
		}
		else {
			std::cout << "Impossible\n";
		}
	}
	void operator *= (const Matrix& m) {
		*this = (*this * m);
	}
};

class Vec3d : public Matrix {
public:
	double& x = v[0][0];
	double& y = v[1][0];
	double& z = v[2][0];
	double& w = v[3][0];

	Vec3d() :Matrix() {}
	Vec3d(const std::vector<std::vector<double>> v) : Matrix(v) {}
	Vec3d(const Matrix& m) : Matrix(m) {}
	Vec3d(double x, double y, double z, double w = 1) {
		v[0][0] = x, v[1][0] = y, v[2][0] = z, v[3][0] = w;
	}
	void operator = (const Vec3d& m) {
		this->v = m.v;
	}
};

double vec_dot_product(const Vec3d& v1, const Vec3d& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3d vec_cross_product(const Vec3d& v1, const Vec3d& v2) {
	return Vec3d(v1.y * v2.z - v2.y * v1.z, -(v1.x * v2.z - v1.z * v2.x), v1.x * v2.y - v1.y * v2.x);
}

class Polygon {
public:
	Matrix vertex1, vertex2, vertex3;
	sf::Color color;
public:
	Polygon(const Matrix& vertex1, const  Matrix& vertex2, const Matrix& vertex3, const sf::Color& color) {
		this->vertex1 = vertex1, this->vertex2 = vertex2, this->vertex3 = vertex3, this->color = color;
	}
};

class Mesh {
protected:
	std::vector<Polygon> polygon_array;
	Vec3d position;
	double scale;
	double angle_x = 0, angle_z = 0;
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

			// Local cache of verts
			std::vector<Vec3d> verts;

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
				}

				if (line[0] == 'f')
				{
					int f[3];
					s >> junk >> f[0] >> f[1] >> f[2];
					int r = rand() % 100;
					polygon_array.push_back(Polygon(verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1], sf::Color(75 + r, 100 + r, 100 + r)));
				}
			}
			std::cout << polygon_array.size() << std::endl;
		}
	}
	void update() {
		//Move origin

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			position.y += 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			position.y -= 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			position.x += 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			position.x -= 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			position.z += 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			position.z -= 0.1;
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
	}
	void draw(sf::RenderWindow& window) {

		Matrix p({
			{ (WIDTH / HEIGHT) / (std::tan((FIELD_OF_VIEW / 2) * PI / 180)),0,0,0},
			{ 0, 1 / (std::tan((FIELD_OF_VIEW / 2) * PI / 180)),0,0},
			{ 0,0,Z_FAR / (Z_FAR - Z_NEAR),-Z_FAR * Z_NEAR / (Z_FAR - Z_NEAR) },   // 1 / (std::tan(FIELD_OF_VIEW / 2 * PI / 180))
			{ 0,0,1,0 },
			});

		Matrix t({
			{1,0,0,position.x},
			{0,1,0,position.y},
			{0,0,1,position.z},
			{0,0,0,1},
			});

		Matrix a({
			{1,0,0,0},
			{0, std::cos(angle_x * PI / 180),-std::sin(angle_x * PI / 180),0},
			{0, std::sin(angle_x * PI / 180),std::cos(angle_x * PI / 180),0},
			{0,0,0,1}
			});

		Matrix b({
			{std::cos(angle_z * PI / 180),0,std::sin(angle_z * PI / 180),0},
			{0, 1,0,0},
			{-std::sin(angle_z * PI / 180), 0,std::cos(angle_z * PI / 180),0},
			{0,0,0,1}
			});


		std::vector<sf::VertexArray> tris;
		std::vector<sf::Vector2f> z_buffer;
		int index = 0;

		for (auto el : polygon_array) {

			sf::VertexArray tri(sf::Triangles, 3);
			tri[0].color = el.color;
			tri[1].color = el.color;
			tri[2].color = el.color;

			Vec3d  transformed_v1 = t * a * b * el.vertex1;
			Vec3d  transformed_v2 = t * a * b * el.vertex2;
			Vec3d  transformed_v3 = t * a * b * el.vertex3;

			// cross product of 2 vectors
			Vec3d v1v2(transformed_v2.x - transformed_v1.x, transformed_v2.y - transformed_v1.y, transformed_v2.z - transformed_v1.z);
			Vec3d v1v3(transformed_v3.x - transformed_v1.x, transformed_v3.y - transformed_v1.y, transformed_v3.z - transformed_v1.z);
			Vec3d normal = vec_cross_product(v1v2, v1v3);


			Vec3d v1 = p * transformed_v1; // 3d to 2d
			Vec3d v2 = p * transformed_v2;
			Vec3d v3 = p * transformed_v3;

			if (vec_dot_product(normal, Vec3d((transformed_v1.x + transformed_v2.x + transformed_v3.x) / 3, (transformed_v1.y + transformed_v2.y + transformed_v3.y) / 3, (transformed_v1.z + transformed_v2.z + transformed_v3.z) / 3)) < 0) { // Vec3d(position.x, position.y, position.z)

				if (v1.w != 0) {
					v1.x /= v1.w;
					v1.y /= v1.w;
					v1.z /= v1.w;
				}

				if (v2.w != 0) {
					v2.x /= v2.w;
					v2.y /= v2.w;
					v2.z /= v2.w;
				}

				if (v3.w != 0) {
					v3.x /= v3.w;
					v3.y /= v3.w;
					v3.z /= v3.w;
				}

				tri[0].position = sf::Vector2f(v1.x * scale + WIDTH / 2, v1.y * scale + HEIGHT / 2);
				tri[1].position = sf::Vector2f(v2.x * scale + WIDTH / 2, v2.y * scale + HEIGHT / 2);
				tri[2].position = sf::Vector2f(v3.x * scale + WIDTH / 2, v3.y * scale + HEIGHT / 2);

				tris.push_back(tri);
				z_buffer.push_back(sf::Vector2f((transformed_v1.z + transformed_v2.z + transformed_v3.z) / 3, index));
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

	Mesh c(Vec3d(0, 0, 10), 300);
	c.LoadFromFile("teapot.obj");


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
	}



	return 0;
}