//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#pragma region Constructors
  Vec4::Vec4() {
    vec_ = _mm_setzero_ps();
  }

  Vec4::Vec4(const Vec4& o) {
    vec_ = o.vec_;
  }

  Vec4::Vec4(const Vec3& o, const float u4) {
    vec_ = _mm_set_ps(u4, o.z(), o.y(), o.x());   //high to low MSB u4|z|y|x LSB
  }

  Vec4::Vec4(const float u1, const float u2, const float u3, const float u4) {
    vec_ = _mm_set_ps(u4, u3, u2, u1);          //high to low MSB u4|u3|u2|u1 LSB
  }

  Vec4::Vec4(const __m128 o) {
    vec_ = o;
  }
#pragma endregion

#pragma region Components
  const float Vec4::x() const {
    return vec_.m128_f32[X];
  }

  float& Vec4::x() {
    return vec_.m128_f32[X];
  }

  const float Vec4::y() const {
    return vec_.m128_f32[Y];
  }

  float& Vec4::y() {
    return vec_.m128_f32[Y];
  }

  const float Vec4::z() const {
    return vec_.m128_f32[Z];
  }

  float& Vec4::z() {
    return vec_.m128_f32[Z];
  }

  const float Vec4::w() const {
    return vec_.m128_f32[W];
  }

  float& Vec4::w() {
    return vec_.m128_f32[W];
  }

  const __m128 Vec4::sse_val() const {
    return vec_;
  }

  __m128& Vec4::sse_val() {
    return vec_;
  }
#pragma endregion

#pragma region Operators
  Vec4& Vec4::operator=(const Vec4& o) {
    if (this != &o) {
      vec_ = o.vec_;
    }
    return *this;
  }

  const float Vec4::operator[](uint16_t index) const {  
    assert(index < 4);
    return vec_.m128_f32[index];
  }

  float& Vec4::operator[](uint16_t index) {  
    assert(index < 4);
    return vec_.m128_f32[index];
  }

  const Vec4 Vec4::operator-() const {
    return Vec4(-vec_.m128_f32[X], -vec_.m128_f32[Y], -vec_.m128_f32[Z], -vec_.m128_f32[W]);
  }
#pragma endregion

#pragma region Named Operators
  Vec4& Vec4::addEq(const Vec4& o) {
    vec_ = _mm_add_ps(vec_, o.vec_);
    return *this;
  }

  Vec4& Vec4::subEq(const Vec4& o) {
    vec_ = _mm_sub_ps(vec_, o.vec_);
    return *this;
  }

  Vec4& Vec4::multEq(const float o) {
    __m128 aux = _mm_set1_ps(o);
    vec_ = _mm_mul_ps(vec_, aux);
    return *this;
  }

  Vec4& Vec4::divEq(const float o) {
    assert(o != 0.0f);
    __m128 aux = _mm_set1_ps(o);
    vec_ = _mm_div_ps(vec_, aux);
    return *this;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec4::dot(const Vec4& o) const {
    __m128 aux=_mm_mul_ps(vec_,o.vec_);
    aux=_mm_hadd_ps(aux,aux);
    aux=_mm_hadd_ps(aux,aux);
    float res;
    _mm_store_ss(&res,aux);
    return res;
  }

  float Vec4::length() const {
    __m128 aux = _mm_mul_ps(vec_, vec_);
    aux = _mm_hadd_ps(aux, aux);
    float res;
    _mm_store_ss(&res, _mm_sqrt_ps(_mm_hadd_ps(aux, aux)));
    return res;
  }

  const Vec4 Vec4::normalized() const {
    __m128 aux = _mm_mul_ps(vec_, vec_);    
    aux = _mm_hadd_ps(aux, aux);
    return Vec4(_mm_div_ps(vec_, _mm_sqrt_ps(_mm_hadd_ps(aux, aux))));
  }
#pragma endregion

#pragma region Additional
  void Vec4::zeros() {
    vec_ = _mm_setzero_ps();
  }
#pragma endregion