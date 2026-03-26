#include "Simplex.h"

#include <cassert>
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        Simplex::Simplex(const Vector3* location)
        {
          positions = new SupportVertex[4];
          size = 0;
          this->location = location;
        }

        Simplex::Simplex(const Simplex& simplex)
        {
          location = simplex.location;
          positions = new SupportVertex[4];
          size = simplex.size;
          for(unsigned int i=0;i<size;i++)
          {
            *(positions + i) = *(simplex.positions + i);
          }
        }

        Simplex& Simplex::operator=(const Simplex& simplex)
        {
          delete[] positions;
          positions = new SupportVertex[4];
          size = simplex.size;
          for(unsigned int i=0;i<size;i++)
          {
            *(positions + i) = *(simplex.positions + i);
          }
          location = simplex.location;
          return *this;
        }

        Simplex::~Simplex()
        {
          delete[] positions;
        }

        const SupportVertex& Simplex::operator[](unsigned int index) const
        {
          assert(index < size);
          return *(positions + index);
        }

        void Simplex::forceAdd(const SupportVertex& sv)
        {
          assert(size < 4);
          *(positions + size) = sv;
          size++;
        }

        void Simplex::processLine(const SupportVertex& position)
        {
          Vector3 OA = positions->getMDifference();
          Vector3 OB = position.getMDifference();
          Vector3 AB = OB - OA;
          Vector3 BL = (*location) - OB;
          Vector3 AL = (*location) - OA;
          if(AB.dot(BL) > 0.0)
          {
            //A
            size = 1;
            *positions = position;
          }
          else if(AB.dot(AL) < 0.0)
          {
            size = 1;
          }
          else
          {
            //B
            size = 2;
            *(positions + 1) = position;
          }
        }

        void Simplex::processTriangle(const SupportVertex& position)
        {
          Vector3 OA = positions->getMDifference();
          Vector3 OB = (positions + 1)->getMDifference();
          Vector3 OC = position.getMDifference();

          Vector3 AB = OB - OA;
          Vector3 BC = OC - OB;
          Vector3 CA = OA - OC;

          Vector3 AL = (*location) - OA;
          Vector3 BL = (*location) - OB;
          Vector3 CL = (*location) - OC;

          //A
          float ABAL = AB.dot(AL);
          float ACAL = -CA.dot(AL);

          //B
          float BCBL = BC.dot(BL);
          float BABL = -AB.dot(BL);

          //C
          float CACL = CA.dot(CL);
          float CBCL = -BC.dot(CL);

          if(ABAL < 0.0 && ACAL < 0.0)
          {
            //A
            size = 1;
          }
          else if(BCBL < 0.0 && BABL < 0.0)
          {
            //B
            *positions = *(positions + 1);
            size = 1;
          }
          else if(CACL < 0.0 && CBCL < 0.0)
          {
            //C
            *positions = position;
            size = 1;
          }
          else
          {
            Vector3 nABC = AB.cross(BC);
            Vector3 nAB = AB.cross(nABC);
            Vector3 nBC = BC.cross(nABC);
            Vector3 nCA = CA.cross(nABC);

            //AB
            float nABdAL = nAB.dot(AL);
            //BC
            float nBCdBL = nBC.dot(BL);
            //CA
            float nCAdCL = nCA.dot(CL);

            if(ABAL > 0.0 && BABL > 0.0 && nABdAL > 0.0)
            {
              //AB
              size = 2;
            }
            else if(BCBL > 0.0 && CBCL > 0.0 && nBCdBL > 0.0)
            {
              //BC
              *positions = position;
              size = 2;
            }
            else if(CACL > 0.0 && ACAL > 0.0 && nCAdCL > 0.0)
            {
              //CA
              *(positions + 1) = position;
              size = 2;
            }
            else if(nABC.dot(AL) >= 0.0)
            {
              //ABC
              *(positions + 2) = position;
              size = 3;
            }
            else
            {
              //ACB
              *(positions + 2) = *(positions + 1);
              *(positions + 1) = position;
              size = 3;
            }
          }

        }

        void Simplex::processTetrahedron(const SupportVertex& position)
        {
          Vector3 OA = positions->getMDifference();
          Vector3 OB = (positions + 1)->getMDifference();
          Vector3 OC = (positions + 2)->getMDifference();
          Vector3 OD = position.getMDifference();

          Vector3 AB = OB - OA;
          Vector3 BC = OC - OB;
          Vector3 CA = OA - OC;

          Vector3 AD = OD - OA;
          Vector3 BD = OD - OB;
          Vector3 CD = OD - OC;

          Vector3 nABC = BC.cross(AB);
          Vector3 nABD = AB.cross(AD);
          Vector3 nBCD = BC.cross(BD);
          Vector3 nCAD = CA.cross(CD);
          //OK

          Vector3 AL = (*location) - OA;
          Vector3 BL = (*location) - OB;
          Vector3 CL = (*location) - OC;
          Vector3 DL = (*location) - OD;

          //A
          float ABAL = AB.dot(AL);
          float ACAL = -CA.dot(AL);
          float ADAL = AD.dot(AL);

          //B
          float BCBL = BC.dot(BL);
          float BABL = -AB.dot(BL);
          float BDBL = BD.dot(BL);

          //C
          float CACL = CA.dot(CL);
          float CBCL = -BC.dot(CL);
          float CDCL = CD.dot(CL);

          //D
          float DADL = -AD.dot(DL);
          float DBDL = -BD.dot(DL);
          float DCDL = -CD.dot(DL);

          //OK

          if(ABAL < 0.0 && ACAL < 0.0 && ADAL < 0.0)
          {
            //A
            size = 1;
          }
          else if(BCBL < 0.0 && BABL < 0.0 && BDBL < 0.0)
          {
            //B
            size = 1;
            *positions = *(positions + 1);
          }
          else if(CACL < 0.0 && CBCL < 0.0 && CDCL < 0.0)
          {
            //C
            size = 1;
            *positions = *(positions + 2);
          }
          else if(DADL < 0.0 && DBDL < 0.0 && DCDL < 0.0)
          {
            //D
            size = 1;
            *positions = position;
          }
          else
          {
            //OK

            //ABC
            Vector3 nABCsAB = nABC.cross(AB);
            Vector3 nABCsBC = nABC.cross(BC);
            Vector3 nABCsCA = nABC.cross(CA);

            //ABD
            Vector3 nABDsAB = AB.cross(nABD);
            Vector3 nABDsBD = BD.cross(nABD);
            Vector3 nABDsDA = nABD.cross(AD);

            //BCD
            Vector3 nBCDsBC = BC.cross(nBCD);
            Vector3 nBCDsCD = CD.cross(nBCD);
            Vector3 nBCDsDB = nBCD.cross(BD);

            //CAD
            Vector3 nCADsCA = CA.cross(nCAD);
            Vector3 nCADsAD = AD.cross(nCAD);
            Vector3 nCADsDC = nCAD.cross(CD);

            //AD
            float DLnABDsDA = DL.dot(nABDsDA);
            float DLnCADsAD = DL.dot(nCADsAD);

            //BD
            float DLnABDsBD = DL.dot(nABDsBD);
            float DLnBCDsDB = DL.dot(nBCDsDB);

            //CD
            float DLnBCDsCD = DL.dot(nBCDsCD);
            float DLnCADsDC = DL.dot(nCADsDC);

            //AB
            float ALnABCsAB = AL.dot(nABCsAB);
            float ALnABDsAB = AL.dot(nABDsAB);

            //BC
            float BLnABCsBC = BL.dot(nABCsBC);
            float BLnBCDsBC = BL.dot(nBCDsBC);

            //CA
            float CLnABCsCA = CL.dot(nABCsCA);
            float CLnCADsCA = CL.dot(nCADsCA);
            //OK

            if(ABAL > 0.0 && BABL > 0.0 && ALnABCsAB > 0.0 && ALnABDsAB > 0.0)
            {
              //AB
              size = 2;
            }
            else if(BCBL > 0.0 && CBCL > 0.0 && BLnABCsBC > 0.0 && BLnBCDsBC > 0.0)
            {
              //BC
              size = 2;
              *positions = *(positions + 2);
            }
            else if(CACL > 0.0 && ACAL > 0.0 && CLnABCsCA > 0.0 && CLnCADsCA > 0.0)
            {
              //CA
              size = 2;
              *(positions + 1) = *(positions + 2);
            }
            else if(ADAL > 0.0 && DADL > 0.0 && DLnABDsDA > 0.0 && DLnCADsAD > 0.0)
            {
              //AD
              size = 2;
              *(positions + 1) = position;
            }
            else if(BDBL > 0.0 && DBDL > 0.0 && DLnABDsBD > 0.0 && DLnBCDsDB > 0.0)
            {
              //BD
              size = 2;
              *positions = position;
            }
            else if(CDCL > 0.0 && DCDL > 0.0 && DLnBCDsCD > 0.0 && DLnCADsDC > 0.0)
            {
              //CD
              size = 2;
              *positions = *(positions + 2);
              *(positions + 1) = position;
            }
            else
            {
              //OK

              float DLnABD = DL.dot(nABD);
              float DLnBCD = DL.dot(nBCD);
              float DLnCAD = DL.dot(nCAD);
              float ALnABC = AL.dot(nABC);

              if(ALnABC > 0.0 && ALnABCsAB < 0.0 && BLnABCsBC < 0.0 && CLnABCsCA < 0.0)
              {
                //ABC
                size = 3;
              }
              if(DLnABD > 0.0 && ALnABDsAB < 0.0 && DLnABDsBD < 0.0 && DLnABDsDA < 0.0)
              {
                //ABD
                size = 3;
                *(positions + 2) = position;
              }
              else if(DLnBCD > 0.0 && BLnBCDsBC < 0.0 && DLnBCDsCD < 0.0 && DLnBCDsDB < 0.0)
              {
                //BCD = DBC
                size = 3;
                *positions = position;
              }
              else if(DLnCAD > 0.0 && CLnCADsCA < 0.0 && DLnCADsAD < 0.0 && DLnCADsDC < 0.0)
              {
                //CAD = ADC
                size = 3;
                *(positions + 1) = position;
              }
              else
              {
                //ABCD
                size = 4;
                *(positions + 3) = position;
              }
            }
          }
        }

        unsigned int Simplex::getSize() const
        {
          return size;
        }

        bool Simplex::contains(const SupportVertex& sv) const
        {
          Vector3 svmd = sv.getMDifference();
          for(unsigned int i=0;i<size;i++)
          {
            Vector3 svmd2 = (positions + i)->getMDifference();
            Vector3 delta = svmd - svmd2;
            if(delta.dot(delta) < 0.00000001)
            {
              return true;
            }
          }
          return false;
        }

        void Simplex::add(const SupportVertex& position)
        {
          if(size == 0)
          {
            //std::cout << "processing point" << std::endl;
            *positions = position;
            size = 1;
          }
          else if(size == 1)
          {
            //std::cout << "processing line" << std::endl;
            processLine(position);
          }
          else if(size == 2)
          {
            //std::cout << "processing triangle" << std::endl;
            processTriangle(position);
          }
          else if(size == 3)
          {
            //std::cout << "processing tetra" << std::endl;
            processTetrahedron(position);
          }
        }

        void Simplex::calculateBC(float* u, float* v, bool* dbz) const
        {
          Vector3 OA = positions->getMDifference();
          Vector3 OB = (positions + 1)->getMDifference();

          Vector3 AB = OB - OA;
          Vector3 AL = (*location) - OA;
          float ABAB = AB.dot(AB);

          if(ABAB == 0.0)
          {
            *dbz = true;
            return;
          }
          *dbz = false;

          *v = AB.dot(AL)/ABAB;
          *u = 1.0 - *v;
        }

        void Simplex::calculateBC(float* u, float* v, float* w, bool* dbz) const
        {
          Vector3 OA = positions->getMDifference();
          Vector3 OB = (positions + 1)->getMDifference();
          Vector3 OC = (positions + 2)->getMDifference();

          Vector3 AB = OB - OA;
          Vector3 AC = OC - OA;
          Vector3 AL = (*location) - OA;

          float ABAB = AB.dot(AB);
          float ABAC = AB.dot(AC);
          float ABAL = AB.dot(AL);

          float ACAC = AC.dot(AC);
          float ACAL = AC.dot(AL);

          float denom = ABAB*ACAC - ABAC*ABAC;
          if(denom == 0.0)
          {
            *dbz = true;
            //std::cout << "denom 0: " << denom << std::endl;
            //OA.print();
            //OB.print();
            //OC.print();
            return;
          }
          *dbz = false;

          *v = (ABAL*ACAC - ACAL*ABAC)/denom;
          *w = (ABAB*ACAL - ABAC*ABAL)/denom;

          *u = 1.0 - *v - *w;
        }

        void Simplex::getClosestPosition(SupportVertex* position, bool* dbz) const
        {
          assert(size > 0);
          if(size == 1)
          {
            *dbz = false;
            *position = *positions;
          }
          else if(size == 2)
          {
            float u;
            float v;
            calculateBC(&u, &v, dbz);
            *position = u*(*positions) + v*(*(positions + 1));
          }
          else if(size == 3)
          {
            float u;
            float v;
            float w;
            calculateBC(&u, &v, &w, dbz);
            *position = u*(*positions) + v*(*(positions + 1)) + w*(*(positions + 2));
          }
          else
          {
            *position = SupportVertex();
          }
        }
      }
    }
  }
}
