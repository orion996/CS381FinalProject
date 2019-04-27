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
	BlackShirt,
	WhiteShirt,
	OrangeShirt

};
enum Hat {
	NoHat,
	BlackHat,
	YellowHat,
	RedHat,
	PurpleHat

};
enum Skin {
	PurpleSkin,
	GreenSkin,
	RedSkin,
	YellowSkin,
	BlueSkin
};

struct Description
{
	Shirt dShirt;
	Hat dHat;
	Skin dSkin;
};



#endif /* INC_DESCRIPTION_H_ */
