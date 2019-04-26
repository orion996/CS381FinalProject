/*
 * Description.h
 *
 *  Created on: Apr 22, 2019
 *      Author: orion996
 */

#ifndef INC_DESCRIPTION_H_
#define INC_DESCRIPTION_H_

enum Shirt {
	RedShirt,
	BlueShirt,
	GreenShirt,
	PurpleShirt,
	YellowShirt

};
enum Hat {
	NoHat,
	BlackHat,
	YellowHat,
	RedHat,
	PurpleHat

};
enum Skin {
	WhiteSkin,
	BlackSkin,
	RedSkin,
	OrangeSkin,
	BlueSkin
};

struct Description
{
	Shirt dShirt;
	Hat dHat;
	Skin dSkin;
};



#endif /* INC_DESCRIPTION_H_ */
