#define GLCD_CHART_LIN_X    0
#define GLCD_CHART_LOG_X    1
#define GLCD_CHART_LIN_Y    0
#define GLCD_CHART_DB_Y     2


class GlcdChart{
private:
    float *data;
    int data_size;
    int x;
    int y;
    int x_size;
    int y_size;
    float cursor;
    float cursor_size;
    int border;
    int axis;
    int options;
    float ymin;
    float yminR;
    float ymax;
    float ymaxR;
    bool y_max_lim;
    bool y_min_lim;
    bool y_range_min;
    bool y_range_max;
    float max_value;
    float min_value;
public:
    GlcdChart();
    void setData(float * data, int size);
    void setSize(int x1, int y1, int x2, int y2);
    void setYLimits(float ymin, float ymax, bool y_min_lim, bool y_max_lim);
    void setYRange(float yminR, float ymaxR, bool y_range_min, bool y_range_max);
    void setAxis(int x, int y);
    void setOptions(int options);
    void draw(int x_min, int x_max);
};
