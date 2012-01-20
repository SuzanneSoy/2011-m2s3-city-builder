#include "all_includes.hh"

const unsigned int Couleurs::fog = mix(cielHaut, cielBas, 0.5);

const float Dimensions::splitFactor = 7.f;
const float Dimensions::mergeFactor = 8.f;
const float Dimensions::frontFrustum = 1.f;
const float Dimensions::backFrustum = 4000 * 100; // 4km
