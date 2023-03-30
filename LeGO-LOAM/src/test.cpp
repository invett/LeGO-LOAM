#include <tf2/LinearMath/Quaternion.h>
#include "utility.h"

int main(int argc, char** argv)
{
    tf2::Quaternion q,r;

    q.setW(0.546003);
    q.setX(0.0147296);
    q.setY(0.0682534);
    q.setZ(0.834868);

    r.setW(0.546003);
    r.setX(0.0147296);
    r.setY(0.0682534);
    r.setZ(0.834868);

    srand (time(NULL));

    for (double i=M_PI;i>0; i=i-0.0001)
        //for (double i=0;i<1000; i++)
    {
        double r1 = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/M_PI));
        double r2 = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/M_PI));
        double r3 = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/M_PI));

        q.setRPY(0.0,0.0,i);
        //q.setRPY(r1,r2,r3);
        r.setRPY(0.0,0.0,i);

        double d1 = q.angleShortestPath(r);

        cout << "----------------------" << endl;
        cout << std::setprecision(20) << "test                 " << i << endl;
        //cout << std::setprecision(10) << "angle:               " << q.angle(r) << endl;
        cout << std::setprecision(20) << "shortest:            " << d1 << endl;

        double t = r[0]*q[0] + r[1]*q[1] + r[2]*q[2] + r[3]*q[3];
        double d2 = 2.0 * acos(fabs(t));
        cout << std::setprecision(20) << "dist acos originale: " << d2 << endl;

        tf2::Quaternion tt = q*r.inverse();
        double d3=2.0 * atan2(sqrt(tt.getX()*tt.getX()+tt.getY()*tt.getY()+tt.getZ()*tt.getZ()), fabs(tt.getW()));
        cout << std::setprecision(20) << "atan2                " << d3 << endl;

        if (fabs(d1-d3)>0.0000001){
            cout << "a\t" << fabs(d1-d3) << endl;
            return 1;
        }

        if (fabs(d2-d3)>0.0000001){
            cout << "a\t" << fabs(d2-d3) << endl;
            return 1;
        }

    }

    cout << "OK" << endl;

    return 0;

}
