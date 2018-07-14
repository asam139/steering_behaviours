//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#pragma region Constructors
  Vec3::Vec3() {
    vec_ = _mm_setzero_ps();
  }

  Vec3::Vec3(const Vec3& o) {
    vec_ = o.vec_;
  }

  Vec3::Vec3(const float u1, const float u2, const float u3) {
    vec_ = _mm_set_ps(0.0f, u3, u2, u1);          //high to low MSB u4|u3|u2|u1 LSB
  }

  Vec3::Vec3(const __m128 o) {
    vec_ = o;
  }
#pragma endregion

#pragma region Components
  const float Vec3::x() const {
    return vec_.m128_f32[X];
  }

  float& Vec3::x() {
    return vec_.m128_f32[X];
  }

  const float Vec3::y() const {
    return vec_.m128_f32[Y];
  }

  float& Vec3::y() {
    return vec_.m128_f32[Y];
  }

  const float Vec3::z() const {
    return vec_.m128_f32[Z];
  }

  float& Vec3::z() {
    return vec_.m128_f32[Z];
  }

  const __m128 Vec3::sse_val() const {
    return vec_;
  }

  __m128& Vec3::sse_val() {
    return vec_;
  }
#pragma endregion

#pragma region Operators
  Vec3& Vec3::operator=(const Vec3& o) {
    if (this != &o) {
      vec_ = o.vec_;
    }
    return *this;
  }

  const float Vec3::operator[](uint16_t index) const {  
    assert(index < 3);
    return vec_.m128_f32[index];
  }

  float& Vec3::operator[](uint16_t index) {  
    assert(index < 3);
    return vec_.m128_f32[index];
  }

  const Vec3 Vec3::operator-() const {
    return Vec3(-vec_.m128_f32[X], -vec_.m128_f32[Y], - vec_.m128_f32[Z]);
  }
#pragma endregion

#pragma region Named Operators
  Vec3& Vec3::addEq(const Vec3& o) {
    vec_ = _mm_add_ps(vec_, o.vec_);
    return *this;
  }

  Vec3& Vec3::subEq(const Vec3& o) {
    vec_ = _mm_sub_ps(vec_, o.vec_);
    return *this;
  }

  Vec3& Vec3::multEq(const float o) {
    __m128 aux = _mm_set1_ps(o);
    vec_ = _mm_mul_ps(vec_, aux);
    return *this;
  }

  Vec3& Vec3::divEq(const float o) {
    assert(o != 0.0f);
    __m128 aux = _mm_set1_ps(o);
    vec_ = _mm_div_ps(vec_, aux);
    return *this;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec3::dot(const Vec3& o) const {
    __m128 aux=_mm_mul_ps(vec_,o.vec_);
    aux=_mm_hadd_ps(aux,aux);
    aux=_mm_hadd_ps(aux,aux);
    float res;
    _mm_store_ss(&res,aux);
    return res;
  }

  float Vec3::length() const {
    __m128 aux = _mm_mul_ps(vec_, vec_);
    aux = _mm_hadd_ps(aux, aux);
    float res;
    _mm_store_ss(&res, _mm_sqrt_ps(_mm_hadd_ps(aux, aux)));
    return res;
  }

  const Vec3 Vec3::normalized() const {
    __m128 aux = _mm_mul_ps(vec_, vec_);    
    aux = _mm_hadd_ps(aux, aux);
    return Vec3(_mm_div_ps(vec_, _mm_sqrt_ps(_mm_hadd_ps(aux, aux))));
  }

  const Vec3 Vec3::cross(const Vec3& o) const {
    return Vec3(_mm_sub_ps(
      _mm_mul_ps(_mm_shuffle_ps(vec_, vec_, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(o.vec_, o.vec_, _MM_SHUFFLE(3, 1, 0, 2))),
      _mm_mul_ps(_mm_shuffle_ps(vec_, vec_, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(o.vec_, o.vec_, _MM_SHUFFLE(3, 0, 2, 1)))));
  }
#pragma endregion

#pragma region Additional
  void Vec3::zeros() {
    vec_ = _mm_setzero_ps();
  }
#pragma endregion