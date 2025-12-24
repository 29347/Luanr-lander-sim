#include <iostream>
#include <thread>
#include <cmath>
#include <chrono>
#include <stdlib.h>

class LanderPhysics
{
private:
    double position;
    double velocity;
    double mass;
    double fuel;
    const double Gravity = -1.625;
    const double Max_Thrust = 4500;
    const double Fuel_burn_rate = 1.5;

public:
    LanderPhysics() : position(50), velocity(-10), mass(1000), fuel(100) {}
    void update(double dt, double throttle)
    {
        if (throttle > 1.0)
            throttle = 1.0;
        if (throttle < 0.0)
            throttle = 0.0;

        if (fuel <= 0)
        {
            throttle = 0.0;
        }
        double thrust_force = throttle * Max_Thrust;
        double force_gravity = mass * Gravity;
        double net_force = thrust_force + force_gravity;

        double acceleration = net_force / mass;
        velocity += acceleration * dt;
        position += velocity * dt;
        double fuel_used = throttle * Fuel_burn_rate * dt;
        fuel -= fuel_used;
    }
    double getAltitude() { return position; }
    double getVelocity() { return velocity; }
    double getFuel() { return fuel; }
};
class PIDcontroller
{
private:
    double kp;
    double ki;
    double kd;

    double previous_error;
    double integral;

public:
    PIDcontroller(double p, double i, double d)
        : kp(p), ki(i), kd(d), previous_error(0.0), integral(0.0) {}
    double calculate(double target_velocity, double current_velocity, double dt)
    {
        double error = target_velocity - current_velocity;
        double p_term = kp * error;
        integral += error * dt;
        double i_term = ki * integral;
        double derivative = (error - previous_error) / dt;
        double d_term = kd * derivative;
        previous_error = error;
        double base_hover_throttle = 0.361;
        return base_hover_throttle + p_term + i_term + d_term;
    }
};
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void drawLander(double altitude, double throttle)
{
    int lines_to_ground = (int)(altitude / 1.0);
    if (lines_to_ground > 25)
        lines_to_ground = 25;
    if (lines_to_ground < 0)
        lines_to_ground = 0;

    for (int i = 0; i < (25 - lines_to_ground); i++)
    {
        std::cout << "\n";
    }

    std::cout << "     /\\\n";
    std::cout << "    /  \\\n";
    std::cout << "   | LM |  <- " << (int)altitude << "m\n";
    std::cout << "   |____|\n";
    std::cout << "    |  |\n";

    // Better flame effects
    if (throttle > 0.9)
    {
        std::cout << "   /|  |\\\n";
        std::cout << "  / |  | \\     MAX BURN\n";
        std::cout << " <  *  *  >\n";
        std::cout << "  \\ | * | /\n";
        std::cout << "   \\|**|/\n";
    }
    else if (throttle > 0.5)
    {
        std::cout << "    \\  /\n";
        std::cout << "    / \\     HALF POWER\n";
        std::cout << "     *\n";
    }
    else if (throttle > 0.1)
    {
        std::cout << "     v      Idling\n";
    }
    else
    {
        std::cout << "           (No thrust)\n";
    }

    for (int i = 0; i < lines_to_ground; i++)
    {
        std::cout << "\n";
    }

    std::cout << "_____________________________________________________________[ Moon Surface]\n";
}
int main()
{
    LanderPhysics lander;
    PIDcontroller autopilot(0.02, 0.005, 0.2);
    double dt = 0.1;
    double current_time = 0.0;
    std::cout << "Auto pilot engaged. target velocity : -5.0 m/s" << std::endl;
    while (lander.getAltitude() > 0)
    {
        clearScreen();
        double target_velocity = 0.5;
        double throttle = autopilot.calculate(target_velocity, lander.getVelocity(), dt);

        lander.update(dt, throttle);
        current_time += dt;
        drawLander(lander.getAltitude(), throttle);
        std::cout << " Status Dashboard \n";
        std::cout << "Time : " << current_time
                  << "s | Alt : " << lander.getAltitude()
                  << "m | Vel : " << lander.getVelocity() << "m/s"
                  << "m/s | Fuel: " << lander.getFuel()
                  << "m/s | Thr " << throttle * 100 << "%" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Mission Report" << std::endl;
    std::cout << "Touchdown Velocity : " << lander.getVelocity() << "m/s" << std::endl;
    if (lander.getVelocity() > -2.0)
    {
        std::cout << "Status: PERFECT LANDING! \n";
    }
    else if (lander.getVelocity() > -5.0)
    {
        std::cout << "Status: Rough landing (survivors injured)\n";
    }
    else
    {
        std::cout << "Status: CRATER  (RIP)\n";
    }
    return 0;
}
