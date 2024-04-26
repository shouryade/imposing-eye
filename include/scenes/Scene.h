#include <vector>
#include <ctime>

class Scene
{
public:
    Scene(int id, time_t startTime, time_t endTime)
        : id(id), startTime(startTime), endTime(endTime) {}

    virtual void render() = 0;

    int getId() const { return id; }
    time_t getStartTime() const { return startTime; }
    time_t getEndTime() const { return endTime; }

protected:
    int id;
    time_t startTime;
    time_t endTime;
};