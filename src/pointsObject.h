#include<vector>

class connection {
    public:
        unsigned int index1 = 0;
        unsigned int index2 = 1;
        float length = 0;
        float strength = 0;
        float strain = 0;
        connection(unsigned int id1, unsigned int id2, float len, float Strain, float str){
            index1 = id1;
            index2 = id2;
            length = len;
            strain = Strain;
            strength = str;
        }
};

class point {
public:
    unsigned int id;
    std::vector<connection> connections = {};
    float x;
    float y;
    point(float Xin, float Yin, unsigned int ID){
        x = Xin;
        y = Yin;
        id = ID;
    }

    void addConnection(unsigned int otherid, float len, float strain, float strength){
        connection connection(id, otherid, len, strain, strength);
        connections.emplace_back(connection);
    }
};

class points {
    public:
        std::vector<point> points = {};
        void addPoint(float Xin, float Yin, unsigned int id){
            point point(Xin, Yin, id);
            points.emplace_back(point);
        }
};
