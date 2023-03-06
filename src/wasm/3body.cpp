#include <cmath>
#include <array>

struct vec3 {
    double x, y, z;
    vec3() : x(0), y(0), z(0) {}
    vec3(double x, double y, double z) : x(x), y(y), z(z) {}
    vec3(const vec3& v) = default;

    bool operator>(vec3 other){

    }



    vec3& operator+=(const vec3& other){
        x += other.x; y += other.y; z += other.z;
        return *this;
    }
    vec3 operator+(const vec3& other) const {
        return vec3(*this) += other;
    }
    vec3 operator-() const {
        return *this * -1;
    }
    vec3& operator-=(const vec3& other) {
        return *this += -other;
    }
    vec3 operator-(const vec3& other) const {
        return *this + -other;
    }
    vec3& operator*=(const double s){
        x *= s; y *= s; z *= s;
        return *this;
    }
    vec3 operator*(const double s) const {
        return vec3(*this) *= s;
    }
    double operator*(const vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    vec3& operator/=(const double s){
        return *this *= (1./s);
    }
    vec3 operator/(const double s) const {
        return *this * (1./s);
    }
    double operator+() const {
        return sqrt(*this * *this);
    }
    vec3 operator~() const {
        return *this / +*this;
    }
};

struct body {
    double mass;
    vec3 pos, vel, acc {};
    body(vec3 pos = vec3(), vec3 vel = vec3(), double mass = 1)
        : pos{pos}, vel{vel}, mass{mass} {}
    vec3 getGravitationalFieldAt(const vec3& p) const {
        vec3 r = pos - p;
        return ~r * mass / (r * r);
    }
};

template<size_t N> class NBodySystem {
public:
    std::array<body, N> bodies;
    double elapsedTime;
    NBodySystem(std::array<body, N> bodies) : bodies(bodies), elapsedTime(0){}

    void update(size_t times, double timeStep = 0.016){
        while(times --> 0) update(timeStep);
    }

private:
    void update(double timeStep = 0.016){
        for (auto& body : bodies){
            body.pos += ((body.vel + (body.acc * timeStep / 2)) * timeStep);
        }
        for(auto& body : bodies){
            vec3 acc;
            for(auto& other : bodies){
                if(&other == &body) continue;
                acc += other.getGravitationalFieldAt(body.pos);
            }
            body.vel = body.vel + ((body.acc + acc) / 2 * timeStep);
            body.acc = acc;
        }
        elapsedTime += timeStep;
    }
};


void calculate(double* config, size_t times, double timeStep){
    std::array<body, 3> bodies {body{
            {config[0], config[1], config[2]},
            {config[3], config[4], config[5]},
            config[6]
    }, body{
            {config[7], config[8], config[9]},
            {config[10], config[11], config[12]},
            config[13]
    }, body{
            {config[14], config[15], config[16]},
            {config[17], config[18], config[19]},
            config[20]
    }};
    NBodySystem<3> sys(bodies);
    sys.update(times, timeStep);

}