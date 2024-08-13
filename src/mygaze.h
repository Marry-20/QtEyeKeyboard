#ifndef MYGAZE_H
#define MYGAZE_H
#include <gazeapi.h>


class MyGaze : public gtl::IGazeListener
{
public:
    MyGaze();
    ~MyGaze();
private:
    // IGazeListener
    void on_gaze_data( gtl::GazeData const & gaze_data );
private:
    gtl::GazeApi m_api;
};
#endif // MYGAZE_H
