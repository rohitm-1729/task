#include "RAW2PGM.h"
using namespace std;

int RAW2PGM::DebayerImage()
{
    Colored12Bit = new uint16_t[PixelCount*3];
    this->Debayer_corner(Colored12Bit);
	
    for(unsigned int i = 0, j=0; i < PixelCount; i++,j+=3){

		cout<<"hello"<<endl;
        unsigned int eff_row = i/_width;
        unsigned int eff_col = i%_width;
        if(eff_row < 1 || eff_col < 1){
                continue;
            }
        else{
        //choosing pattern based on index
        	unsigned int _choice=0;
        	if(eff_row % 2 == 0 && eff_col % 2 == 0){
            	_choice = 1;
        	}
        	else if (eff_row % 2 == 0 && eff_col % 2 == 1) {
       		 	_choice = 2;
        	}
        	else if (eff_row % 2 == 1 && eff_col % 2 == 0) {
          		_choice = 3;
        	}
        	else {
          		_choice = 4;
        	}

			switch (_choice) {
				case 1:  // PIXEL R
				{
					// Init RGB variables
					uint16_t R;
					uint16_t G;
					uint16_t B;

					// Get G
					uint16_t G1 = Buff12Bit[((eff_row-1) * _width) + eff_col];
					uint16_t G2 = Buff12Bit[ (eff_row) * _width + eff_col + 1];
					
					uint16_t G3 = Buff12Bit[(eff_row+1) * _width + eff_col ];
					
					uint16_t G4 = Buff12Bit[(eff_row * _width) + eff_col - 1];
					

					// Get R
					uint16_t R1 = Buff12Bit[(eff_row-2) * _width + eff_col];
					//bayer.at(bayer.I_c, bayer.I_r - 2)[0];
					uint16_t R2 = Buff12Bit[eff_row * _width + eff_col + 2];
					//bayer.at(bayer.I_c + 2, bayer.I_r)[0];
					uint16_t R3 = Buff12Bit[(eff_row + 2) * _width + eff_col];
					// bayer.at(bayer.I_c, bayer.I_r + 2)[0];
					uint16_t R4 = Buff12Bit[eff_row * _width + eff_col - 2];
					//bayer.at(bayer.I_c - 2, bayer.I_r)[0];

					// Get B
					uint16_t B1 = Buff12Bit[ (eff_row-1) * _width + eff_col - 1];
					// bayer.at(bayer.I_c - 1, bayer.I_r - 1)[0];
					uint16_t B2 = Buff12Bit[ (eff_row-1) * _width + eff_col + 1 ];
					// bayer.at(bayer.I_c + 1, bayer.I_r - 1)[0];
					uint16_t B3 = Buff12Bit[ (eff_row + 1) * _width + eff_col + 1]; 
					//bayer.at(bayer.I_c + 1, bayer.I_r + 1)[0];
					uint16_t B4 = Buff12Bit[ (eff_row + 1) * _width + eff_col - 1];
					//bayer.at(bayer.I_c - 1, bayer.I_r + 1)[0];

					// Assign R
					R = Buff12Bit[i];

					// Assign G
					if (abs(R1 - R3) < abs(R2 - R4)) {
					G = (G1 + G3) / 2;
					} else if (abs(R1 - R3) > abs(R2 - R4)) {
					G = (G2 + G4) / 2;
					} else {
					G = (G1 + G2 + G3 + G4) / 4;
					}

					// Assign B
					B = (B1 + B2 + B3 + B4) / 4;

					// Return BGR
					Colored12Bit[j]=R;
					Colored12Bit[j + 1]=G;
					Colored12Bit[j + 2]=B;
					//return visioncpp::pixel::U8C3(B, G, R);
				} break;
				case 2:  // PIXEL G1
				{
					// Init RGB variables
					uint16_t R;
					uint16_t G;
					uint16_t B;

					// Get R
					uint16_t R1 = Buff12Bit[(eff_row * _width) + eff_col - 1];
					//bayer.at(bayer.I_c - 1, bayer.I_r)[0];
					uint16_t R2 = Buff12Bit[ (eff_row) * _width + eff_col + 1];
					// bayer.at(bayer.I_c + 1, bayer.I_r)[0];

					// Get B
					uint16_t B1 = Buff12Bit[((eff_row-1) * _width) + eff_col];
					//bayer.at(bayer.I_c, bayer.I_r - 1)[0];
					uint16_t B2 = Buff12Bit[(eff_row+1) * _width + eff_col ];
					//bayer.at(bayer.I_c, bayer.I_r + 1)[0];

					// Assign R
					R = (R1 + R2) / 2;

					// Assign G
					G = Buff12Bit[i];
					// Assign B
					B = (B1 + B2) / 2;

					// Return BGR
					Colored12Bit[j]=R;
					Colored12Bit[j + 1]=G;
					Colored12Bit[j + 2]=B;
				} break;
				case 3:  // Pixel G2
				{
					// Init RGB variables
					uint16_t R;
					uint16_t G;
					uint16_t B;

					// Get R
					uint16_t R1 = Buff12Bit[((eff_row-1) * _width) + eff_col];
					//bayer.at(bayer.I_c, bayer.I_r - 1)[0];
					uint16_t R2 = Buff12Bit[(eff_row+1) * _width + eff_col ];
					//bayer.at(bayer.I_c, bayer.I_r + 1)[0];

					// Get B
					uint16_t B1 = Buff12Bit[(eff_row * _width) + eff_col - 1];
					//bayer.at(bayer.I_c - 1, bayer.I_r)[0];
					uint16_t B2 = Buff12Bit[ (eff_row) * _width + eff_col + 1];
					//bayer.at(bayer.I_c + 1, bayer.I_r)[0];

					// Assign R
					R = (R1 + R2) / 2;

					// Assign G
					G = Buff12Bit[i];

					// Assign B
					B = (B1 + B2) / 2;

					// Return BGR
					Colored12Bit[j]=R;
					Colored12Bit[j + 1]=G;
					Colored12Bit[j + 2]=B;
					//return visioncpp::pixel::U8C3(B, G, R);
				} break;
				case 4:  // pixel B
				{
					// Init RGB Values
					uint16_t R;
					uint16_t G;
					uint16_t B;

					// Get G
					uint16_t G1 = Buff12Bit[((eff_row-1) * _width) + eff_col];
					//bayer.at(bayer.I_c, bayer.I_r - 1)[0];
					uint16_t G2 = Buff12Bit[ (eff_row) * _width + eff_col + 1];
					//bayer.at(bayer.I_c + 1, bayer.I_r)[0];
					uint16_t G3 = Buff12Bit[(eff_row+1) * _width + eff_col ];
					//bayer.at(bayer.I_c, bayer.I_r + 1)[0];
					uint16_t G4 = Buff12Bit[(eff_row * _width) + eff_col - 1];
					//bayer.at(bayer.I_c - 1, bayer.I_r)[0];

					// Get B
					uint16_t B1 = Buff12Bit[(eff_row-2) * _width + eff_col];
					//bayer.at(bayer.I_c, bayer.I_r - 2)[0];
					uint16_t B2 = Buff12Bit[eff_row * _width + eff_col + 2];
					//bayer.at(bayer.I_c + 2, bayer.I_r)[0];
					uint16_t B3 = Buff12Bit[(eff_row + 2) * _width + eff_col];
					//bayer.at(bayer.I_c, bayer.I_r + 2)[0];
					uint16_t B4 = Buff12Bit[eff_row * _width + eff_col - 2];
					//bayer.at(bayer.I_c - 2, bayer.I_r)[0];

					// Get R
					uint16_t R1 = Buff12Bit[ (eff_row-1) * _width + eff_col - 1];
					//bayer.at(bayer.I_c - 1, bayer.I_r - 1)[0];
					uint16_t R2 = Buff12Bit[ (eff_row-1) * _width + eff_col + 1 ];
					//bayer.at(bayer.I_c + 1, bayer.I_r - 1)[0];
					uint16_t R3 = Buff12Bit[ (eff_row + 1) * _width + eff_col + 1]; 
					//bayer.at(bayer.I_c + 1, bayer.I_r + 1)[0];
					uint16_t R4 = Buff12Bit[ (eff_row + 1) * _width + eff_col - 1];
					//bayer.at(bayer.I_c - 1, bayer.I_r + 1)[0];

					// Assign R
					R = (R1 + R2 + R3 + R4) / 4;

					// Assign G
					if (abs(B1 - B3) < abs(B2 - B4)) {
					G = (G1 + G3) / 2;
					} else if (abs(B1 - B3) > abs(B2 - B4)) {
					G = (G2 + G4) / 2;
					} else {
					G = (G1 + G2 + G3 + G4) / 4;
					}

					// Assign B
					B = Buff12Bit[i];

					// Return BGR
					Colored12Bit[j]=R;
					Colored12Bit[j + 1]=G;
					Colored12Bit[j + 2]=B;
					//return visioncpp::pixel::U8C3(B, G, R);
				} break;
				default: 
					//return visioncpp::pixel::U8C3(0, 0, 0);  // avoid warning
				break;
				}
			}

    // Colored12Bit = new uint16_t[PixelCount*3];
    // for(unsigned int index = 0;  index < PixelCount; index+=2){
    //     if ((index/_width)%2==0){
    //         //pixel at R and pixel at G
    //         for(unsigned int j=0; j < 6; j+=3){
    //         Colored12Bit[index*3 + j] = Buff12Bit[index];
    //         Colored12Bit[index*3 + j+1] = (Buff12Bit[index + 1] + Buff12Bit[index + _width])/2;
    //         Colored12Bit[index*3 + j+2] = Buff12Bit[index + _width + 1];
    //         }
    //     }else{
    //         for(unsigned int k = 0; k < 6; k+=3){
    //             Colored12Bit[index*3 + k] = Buff12Bit[index - _width];
    //             Colored12Bit[index*3 + k+1] = (Buff12Bit[index]+Buff12Bit[(index - _width) + 1])/2;
    //             Colored12Bit[index*3 + k+2] = Buff12Bit[index + 1];
    //         }
            
    //     }
        
        
    // }
    }
    return 0;
}



