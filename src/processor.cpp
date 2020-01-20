#include "include/processor.h"

ConditionCodes::ConditionCodes() {
  this->z = 0;
  this->s = 0;
  this->p = 0;
  this->cy = 0;
  this->ac = 0;
  this->pad = 0;
}

ConditionCodes::ConditionCodes(uint8_t z, uint8_t s, uint8_t p, uint8_t cy,
                               uint8_t ac, uint8_t pad) {
  this->z = z;
  this->s = s;
  this->p = p;
  this->cy = cy;
  this->ac = ac;
  this->pad = pad;
}

ConditionCodes::ConditionCodes(const ConditionCodes& obj) {
  this->z = obj.z;
  this->s = obj.s;
  this->p = obj.p;
  this->cy = obj.cy;
  this->ac = obj.ac;
  this->pad = obj.pad;
}

ConditionCodes& ConditionCodes::operator=(const ConditionCodes& rhs) {
  if (this == &rhs) return *this;

  this->z = rhs.z;
  this->s = rhs.s;
  this->p = rhs.p;
  this->cy = rhs.cy;
  this->ac = rhs.ac;
  this->pad = rhs.pad;

  return *this;
}

bool ConditionCodes::operator==(const ConditionCodes& rhs) const {
  return (this->z == rhs.z) &&
         (this->s == rhs.s) &&
         (this->p == rhs.p) &&
         (this->cy == rhs.cy) &&
         (this->ac == rhs.ac) &&
         (this->pad == rhs.pad);
}

bool ConditionCodes::operator!=(const ConditionCodes& rhs) const {
  return !(*this == rhs);
}
