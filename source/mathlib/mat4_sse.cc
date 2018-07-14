//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#pragma region Constructors
  Mat4::Mat4() {
    matrix_[0] = _mm_setzero_ps();
    matrix_[1] = _mm_setzero_ps();
    matrix_[2] = _mm_setzero_ps();
    matrix_[3] = _mm_setzero_ps();
  }

  Mat4::Mat4(const Mat4& o) {
    matrix_[0] = o.matrix_[0];
    matrix_[1] = o.matrix_[1];
    matrix_[2] = o.matrix_[2];
    matrix_[3] = o.matrix_[3];
  }

  Mat4::Mat4(const Vec4 &c0, const Vec4 &c1, const Vec4 &c2, const Vec4 &c3) {
    matrix_[0] = c0.sse_val();
    matrix_[1] = c1.sse_val();
    matrix_[2] = c2.sse_val();
    matrix_[3] = c3.sse_val();
  }

  Mat4::Mat4(const float o[16]) {
    matrix_[0] = _mm_set_ps(o[3], o[2], o[1], o[0]);
    matrix_[1] = _mm_set_ps(o[7], o[6], o[5], o[4]);
    matrix_[2] = _mm_set_ps(o[11], o[10], o[9], o[8]);
    matrix_[3] = _mm_set_ps(o[15], o[14], o[13], o[12]); 
  }
#pragma endregion

#pragma region Components
  const Vec4 Mat4::getColumn(unsigned short index) const {
    assert(index<4);
    return Vec4(matrix_[index]);
  }

  const Vec4 Mat4::getRow(unsigned short index) const {
    assert(index<4);
    return Vec4(matrix_[0].m128_f32[index], matrix_[1].m128_f32[index], matrix_[2].m128_f32[index], matrix_[3].m128_f32[index]);
  }

  const __m128 Mat4::getRow_sse(unsigned short index) const {
    assert(index<4);
    return _mm_set_ps(matrix_[0].m128_f32[index], matrix_[1].m128_f32[index], matrix_[2].m128_f32[index], matrix_[3].m128_f32[index]);
  }
#pragma endregion

#pragma region Operators
  Mat4& Mat4::operator=(const Mat4& o) {
    if (this != &o) {
      matrix_[0] = o.matrix_[0];
      matrix_[1] = o.matrix_[1];
      matrix_[2] = o.matrix_[2];
      matrix_[3] = o.matrix_[3]; 
    }
    return *this;
  }
#pragma endregion

#pragma region Named Operators
  Mat4& Mat4::addEq(const Mat4& o) {
    matrix_[0] = _mm_add_ps(matrix_[0], o.matrix_[0]);
    matrix_[1] = _mm_add_ps(matrix_[1], o.matrix_[1]);
    matrix_[2] = _mm_add_ps(matrix_[2], o.matrix_[2]);
    matrix_[3] = _mm_add_ps(matrix_[3], o.matrix_[3]);
    return *this;
  }

  Mat4& Mat4::subEq(const Mat4& o) {
    matrix_[0] = _mm_sub_ps(matrix_[0], o.matrix_[0]);
    matrix_[1] = _mm_sub_ps(matrix_[1], o.matrix_[1]);
    matrix_[2] = _mm_sub_ps(matrix_[2], o.matrix_[2]);
    matrix_[3] = _mm_sub_ps(matrix_[3], o.matrix_[3]);
    return *this;
  }

  Mat4& Mat4::multEq(const Mat4& o) {
    __m128 r0, r1, r2, r3;

    r0 = _mm_add_ps(_mm_add_ps( _mm_mul_ps(matrix_[0], _mm_shuffle_ps(o.matrix_[0], o.matrix_[0], _MM_SHUFFLE(0, 0, 0, 0))),  //Element x Column
                                _mm_mul_ps(matrix_[1], _mm_shuffle_ps(o.matrix_[0], o.matrix_[0], _MM_SHUFFLE(1, 1, 1, 1)))),
                    _mm_add_ps( _mm_mul_ps(matrix_[2], _mm_shuffle_ps(o.matrix_[0], o.matrix_[0], _MM_SHUFFLE(2, 2, 2, 2))),
                                _mm_mul_ps(matrix_[3], _mm_shuffle_ps(o.matrix_[0], o.matrix_[0], _MM_SHUFFLE(3, 3, 3, 3)))));

    r1 = _mm_add_ps(_mm_add_ps( _mm_mul_ps(matrix_[0], _mm_shuffle_ps(o.matrix_[1], o.matrix_[1], _MM_SHUFFLE(0, 0, 0, 0))),
                                _mm_mul_ps(matrix_[1], _mm_shuffle_ps(o.matrix_[1], o.matrix_[1], _MM_SHUFFLE(1, 1, 1, 1)))),
                    _mm_add_ps( _mm_mul_ps(matrix_[2], _mm_shuffle_ps(o.matrix_[1], o.matrix_[1], _MM_SHUFFLE(2, 2, 2, 2))),
                                _mm_mul_ps(matrix_[3], _mm_shuffle_ps(o.matrix_[1], o.matrix_[1], _MM_SHUFFLE(3, 3, 3, 3)))));

    r2 = _mm_add_ps(_mm_add_ps( _mm_mul_ps(matrix_[0], _mm_shuffle_ps(o.matrix_[2], o.matrix_[2], _MM_SHUFFLE(0, 0, 0, 0))),
                                _mm_mul_ps(matrix_[1], _mm_shuffle_ps(o.matrix_[2], o.matrix_[2], _MM_SHUFFLE(1, 1, 1, 1)))),
                    _mm_add_ps( _mm_mul_ps(matrix_[2], _mm_shuffle_ps(o.matrix_[2], o.matrix_[2], _MM_SHUFFLE(2, 2, 2, 2))),
                                _mm_mul_ps(matrix_[3], _mm_shuffle_ps(o.matrix_[2], o.matrix_[2], _MM_SHUFFLE(3, 3, 3, 3)))));

    r3 = _mm_add_ps(_mm_add_ps( _mm_mul_ps(matrix_[0], _mm_shuffle_ps(o.matrix_[3], o.matrix_[3], _MM_SHUFFLE(0, 0, 0, 0))),
                                _mm_mul_ps(matrix_[1], _mm_shuffle_ps(o.matrix_[3], o.matrix_[3], _MM_SHUFFLE(1, 1, 1, 1)))),
                    _mm_add_ps( _mm_mul_ps(matrix_[2], _mm_shuffle_ps(o.matrix_[3], o.matrix_[3], _MM_SHUFFLE(2, 2, 2, 2))),
                                _mm_mul_ps(matrix_[3], _mm_shuffle_ps(o.matrix_[3], o.matrix_[3], _MM_SHUFFLE(3, 3, 3, 3)))));
    matrix_[0] = r0;
    matrix_[1] = r1;
    matrix_[2] = r2;
    matrix_[3] = r3;
    return *this;
  }

  Mat4& Mat4::multEq(const float o) {
    __m128 aux = _mm_set1_ps(o);
    matrix_[0] = _mm_mul_ps(matrix_[0], aux);
    matrix_[1] = _mm_mul_ps(matrix_[1], aux);
    matrix_[2] = _mm_mul_ps(matrix_[2], aux);
    matrix_[3] = _mm_mul_ps(matrix_[3], aux);
    return *this;
  }

  Mat4& Mat4::divEq(const float o) {
    assert(o != 0.0f);
    __m128 aux = _mm_set1_ps(o);
    matrix_[0] = _mm_div_ps(matrix_[0], aux);
    matrix_[1] = _mm_div_ps(matrix_[1], aux);
    matrix_[2] = _mm_div_ps(matrix_[2], aux);
    matrix_[3] = _mm_div_ps(matrix_[3], aux);
    return *this;
  }

  const Vec4 Mat4::mult(const Vec4& o) const {
    __m128 vec = o.sse_val();
    return Vec4(_mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(getRow_sse(0), vec), _mm_mul_ps(getRow_sse(1), vec)),    //Row x Vector
                _mm_hadd_ps(_mm_mul_ps(getRow_sse(2), vec), _mm_mul_ps(getRow_sse(3), vec))));
  }
#pragma endregion

#pragma region Matrix Ops
  const Mat3 Mat4::to3x3() const {
    float aux[9] = {matrix_[0].m128_f32[0], matrix_[0].m128_f32[1], matrix_[0].m128_f32[2],
                    matrix_[1].m128_f32[0], matrix_[1].m128_f32[1], matrix_[1].m128_f32[2],
                    matrix_[2].m128_f32[0], matrix_[2].m128_f32[1], matrix_[2].m128_f32[2] };
    return Mat3(aux);
  }

  const Mat4 Mat4::transpose() const {
    Mat4 aux(*this);
    _MM_TRANSPOSE4_PS(aux.matrix_[0], aux.matrix_[1], aux.matrix_[2], aux.matrix_[3]);
    return aux;
  }

  const Mat4 Mat4::inverse() const {
    __m128 s1, s2;

    s1 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(3, 3, 3, 3));         //Subfactor0
    s2 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(2, 2, 2, 2));
    __m128 f0 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(2, 2, 2, 2)),
      _mm_shuffle_ps(s1, s1, _MM_SHUFFLE(2, 0, 0, 0))),
      _mm_mul_ps(_mm_shuffle_ps(s2, s2, _MM_SHUFFLE(2, 0, 0, 0)),
        _mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(3, 3, 3, 3))));

    s1 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(3, 3, 3, 3));         //Subfactor1
    s2 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(1, 1, 1, 1));
    __m128 f1 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(1, 1, 1, 1)),
      _mm_shuffle_ps(s1, s1, _MM_SHUFFLE(2, 0, 0, 0))),
      _mm_mul_ps(_mm_shuffle_ps(s2, s2, _MM_SHUFFLE(2, 0, 0, 0)),
        _mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(3, 3, 3, 3))));

    s1 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(2, 2, 2, 2));         //Subfactor2
    s2 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(1, 1, 1, 1));
    __m128 f2 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(1, 1, 1, 1)),
      _mm_shuffle_ps(s1, s1, _MM_SHUFFLE(2, 0, 0, 0))),
      _mm_mul_ps(_mm_shuffle_ps(s2, s2, _MM_SHUFFLE(2, 0, 0, 0)),
        _mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(2, 2, 2, 2))));

    s1 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(3, 3, 3, 3));         //Subfactor3
    s2 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(0, 0, 0, 0));
    __m128 f3 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(0, 0, 0, 0)),
      _mm_shuffle_ps(s1, s1, _MM_SHUFFLE(2, 0, 0, 0))),
      _mm_mul_ps(_mm_shuffle_ps(s2, s2, _MM_SHUFFLE(2, 0, 0, 0)),
        _mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(3, 3, 3, 3))));

    s1 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(2, 2, 2, 2));         //Subfactor4
    s2 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(0, 0, 0, 0));
    __m128 f4 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(0, 0, 0, 0)),
      _mm_shuffle_ps(s1, s1, _MM_SHUFFLE(2, 0, 0, 0))),
      _mm_mul_ps(_mm_shuffle_ps(s2, s2, _MM_SHUFFLE(2, 0, 0, 0)),
        _mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(2, 2, 2, 2))));

    s1 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(1, 1, 1, 1));         //Subfactor5
    s2 = _mm_shuffle_ps(matrix_[3], matrix_[2], _MM_SHUFFLE(0, 0, 0, 0));
    __m128 f5 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(0, 0, 0, 0)),
      _mm_shuffle_ps(s1, s1, _MM_SHUFFLE(2, 0, 0, 0))),
      _mm_mul_ps(_mm_shuffle_ps(s2, s2, _MM_SHUFFLE(2, 0, 0, 0)),
        _mm_shuffle_ps(matrix_[2], matrix_[1], _MM_SHUFFLE(1, 1, 1, 1))));


    __m128 sign0 = _mm_set_ps(1.0f, -1.0f, 1.0f, -1.0f);                           //Signs
    __m128 sign1 = _mm_set_ps(-1.0f, 1.0f, -1.0f, 1.0f);

    __m128 t0 = _mm_shuffle_ps(matrix_[1], matrix_[0], _MM_SHUFFLE(0, 0, 0, 0));  //Vectors
    __m128 v0 = _mm_shuffle_ps(t0, t0, _MM_SHUFFLE(2, 2, 2, 0));
    __m128 t1 = _mm_shuffle_ps(matrix_[1], matrix_[0], _MM_SHUFFLE(1, 1, 1, 1));
    __m128 v1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(2, 2, 2, 0));
    __m128 t2 = _mm_shuffle_ps(matrix_[1], matrix_[0], _MM_SHUFFLE(2, 2, 2, 2));
    __m128 v2 = _mm_shuffle_ps(t2, t2, _MM_SHUFFLE(2, 2, 2, 0));
    __m128 t3 = _mm_shuffle_ps(matrix_[1], matrix_[0], _MM_SHUFFLE(3, 3, 3, 3));
    __m128 v3 = _mm_shuffle_ps(t3, t3, _MM_SHUFFLE(2, 2, 2, 0));

    __m128 inv0 = _mm_mul_ps(sign1, _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v1, f0), _mm_mul_ps(v2, f1)),  //Columns
      _mm_mul_ps(v3, f2)));

    __m128 inv1 = _mm_mul_ps(sign0, _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v0, f0), _mm_mul_ps(v2, f3)),
      _mm_mul_ps(v3, f4)));

    __m128 inv2 = _mm_mul_ps(sign1, _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v0, f1), _mm_mul_ps(v1, f3)),
      _mm_mul_ps(v3, f5)));

    __m128 inv3 = _mm_mul_ps(sign0, _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v0, f2), _mm_mul_ps(v1, f4)),
      _mm_mul_ps(v2, f5)));

    __m128 row0 = _mm_shuffle_ps(inv0, inv1, _MM_SHUFFLE(0, 0, 0, 0));            //Rows
    __m128 row1 = _mm_shuffle_ps(inv2, inv3, _MM_SHUFFLE(0, 0, 0, 0));
    __m128 row2 = _mm_shuffle_ps(row0, row1, _MM_SHUFFLE(2, 0, 2, 0));

    __m128 aux = _mm_mul_ps(matrix_[0], row2);       //Dot Product=Determinant
    aux = _mm_hadd_ps(aux, aux);
    __m128 det = _mm_hadd_ps(aux, aux);

    __m128 r = _mm_div_ps(_mm_set_ps1(1.0f), det);  //Det Inv 

    Mat4 res;
    res.matrix_[0] = _mm_mul_ps(inv0, r);           //Columns / Det
    res.matrix_[1] = _mm_mul_ps(inv1, r);
    res.matrix_[2] = _mm_mul_ps(inv2, r);
    res.matrix_[3] = _mm_mul_ps(inv3, r);

    return res;
  }

  const float Mat4::det() const {
    __m128 v1, v2, v3;
    __m128 r1, r2, r3, t1, t2, sum, det;
    float res;

    t1 = matrix_[3];
    t2 = _mm_shuffle_ps(matrix_[2], matrix_[2], _MM_SHUFFLE(0, 3, 2, 1));
    v3 = _mm_mul_ps(t2, t1);
    v1 = _mm_mul_ps(t2, _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2)));
    v2 = _mm_mul_ps(t2, _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(2, 1, 0, 3)));

    r1 = _mm_sub_ps(_mm_shuffle_ps(v1, v1, _MM_SHUFFLE(0, 3, 2, 1)), _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(1, 0, 3, 2)));
    r2 = _mm_sub_ps(_mm_shuffle_ps(v2, v2, _MM_SHUFFLE(1, 0, 3, 2)), v2);
    r3 = _mm_sub_ps(v1, _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(0, 3, 2, 1)));

    v1 = _mm_shuffle_ps(matrix_[1], matrix_[1], _MM_SHUFFLE(0, 3, 2, 1));
    sum = _mm_mul_ps(v1, r1);
    v2 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(0, 3, 2, 1));
    sum = _mm_add_ps(sum, _mm_mul_ps(v2, r2));
    v3 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(0, 3, 2, 1));
    sum = _mm_add_ps(sum, _mm_mul_ps(v3, r3));

    det = _mm_mul_ps(sum, matrix_[0]);
    det = _mm_add_ps(det, _mm_movehl_ps(det, det));
    _mm_store_ss(&res, _mm_sub_ss(det, _mm_shuffle_ps(det, det, 1)));
    return res;
  }
#pragma endregion

#pragma region Additional
  void Mat4::zeros() {
    matrix_[0] = _mm_setzero_ps();
    matrix_[1] = _mm_setzero_ps();
    matrix_[2] = _mm_setzero_ps();
    matrix_[3] = _mm_setzero_ps();
  }
#pragma endregion