# top_jax_boj

백준에 처음 출제한 문제 「이 게임에서 진정한 승자는 누구인가」의 테스트 데이터와 생성기입니다. 잭스와 피오라의 1:1 교전을 다룹니다.

## 구성

| 경로 | 내용 |
|---|---|
| `data/N.in`, `data/N.out` | 테스트 데이터 299쌍 |
| `data/data_generator.cpp` | 없는 번호의 `.in` 파일을 무작위로 생성 |
| `data/out_generator.cpp` | `.in`을 읽어 정답 `.out` 생성 |

## 생성

```sh
cd data
c++ -O2 -std=c++17 -o data_generator data_generator.cpp && ./data_generator
c++ -O2 -std=c++17 -o out_generator out_generator.cpp && ./out_generator
```

## 참고

`data`에는 잘못된 데이터가 몇 개 있습니다. 백준에서는 해당 데이터를 제거했습니다.
