//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#pragma region Constructors
  Vec2::Vec2() {
    vec_ = _mm_setzero_ps();
  }

  Vec2::Vec2(const Vec2& o) {
    vec_ = o.vec_;
  }

  Vec2::Vec2(const float u1, const float u2) {
    vec_ = _mm_set_ps(0, 0, u2, u1);          //high to low MSB u4|u3|u2|u1 LSB
  }

  Vec2::Vec2(const __m128 o) {
    vec_ = o;
  }
#pragma endregion

#pragma region Components
  const float Vec2::x() const {
    return vec_.m128_f32[X];
  }

  float& Vec2::x() {
    return vec_.m128_f32[X];
  }

  const float Vec2::y() const {
    return vec_.m128_f32[Y];
  }

  float& Vec2::y() {
    return vec_.m128_f32[Y];
  }

  const __m128 Vec2::sse_val() const {
    return vec_;
  }

  __m128& Vec2::sse_val() {
    return vec_;
  }
#pragma endregion

#pragma region Operators
  Vec2& Vec2::operator=(const Vec2& o) {
    if (this != &o) {
      vec_ = o.vec_;
    }
    return *this;
  }

  const float Vec2::operator[](uint16_t index) const {  
    assert(index < 2);
    return vec_.m128_f32[index];
  }

  float& Vec2::operator[](uint16_t index) {  
    assert(index < 2);
    return vec_.m128_f32[index];
  }

  const Vec2 Vec2::operator-() const {
    return Vec2(-vec_.m128_f32[X], -vec_.m128_f32[Y]);
  }
#pragma endregion

#pragma region Named Operators
  Vec2& Vec2::addEq(const Vec2& o) {
    vec_ = _mm_add_ps(vec_, o.vec_);
    return *this;
  }

  Vec2& Vec2::subEq(const Vec2& o) {
    vec_ = _mm_sub_ps(vec_, o.vec_);
    return *this;
  }

  Vec2& Vec2::multEq(const float o) {
    __m128 aux = _mm_set1_ps(o);
    vec_ = _mm_mul_ps(vec_, aux);
    return *this;
  }

  Vec2& Vec2::divEq(const float o) {
    assert(o != 0.0f);
    __m128 aux = _mm_set1_ps(o);
    vec_ = _mm_div_ps(vec_, aux);
    return *this;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec2::dot(const Vec2& o) const {
    __m128 aux = _mm_mul_ps(vec_, o.vec_);
    aux = _mm_hadd_ps(aux, aux);
    float res;
    _mm_store_ss(&res, aux);
    return res;
  }

  float Vec2::length() const {
    __m128 aux = _mm_mul_ps(vec_, vec_);
    float res;
    _mm_store_ss(&res, _mm_sqrt_ps(_mm_hadd_ps(aux, aux)));
    return res;
  }

  const Vec2 Vec2::normalized() const {
    __m128 aux = _mm_mul_ps(vec_, vec_);          
    aux = _mm_hadd_ps(aux, aux);
    return Vec2(_mm_div_ps(vec_, _mm_sqrt_ps(_mm_hadd_ps(aux, aux))));
  }
#pragma endregion

#pragma region Additional
  void Vec2::zeros() {
    vec_ = _mm_setzero_ps();
  }

  void Vec2::fromPolar(const float dist, const float ang, const bool use_rads) {
    float rad = ang;
    if (!use_rads) {
      rad *= (float)(M_PI / 180);
    }
    vec_.m128_f32[0] = dist*cos(rad);
    vec_.m128_f32[1] = dist*sin(rad);
  }
#pragma endregion