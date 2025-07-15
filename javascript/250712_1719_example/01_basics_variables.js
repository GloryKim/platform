/**
 * Node.js 기본 문법 - 변수와 데이터 타입
 * 
 * 실행 명령어 : node 01_basics_variables.js
 * 
 * 작동 원리:
 * 1. JavaScript는 동적 타입 언어로, 변수 선언 시 타입을 명시하지 않음
 * 2. let, const, var 키워드로 변수 선언
 * 3. 런타임에 값에 따라 타입이 결정됨
 */

//const { type } = require("os"); //미사용 모듈
//const { getSystemErrorMap } = require("util");//미사용 모듈

console.log('nodejs 변수와 데이터 타입 예제')

console.log('1.변수 선언방법');

var oldEssFunctionScope = "ES5 방식";
    console.log('var:', oldEssFunctionScope);

let new_es6_block_scope = "ES6 방식";
    console.log('var:', new_es6_block_scope);
    new_es6_block_scope = 'adactivate value';
    console.log('let (변경 후 값):', new_es6_block_scope);

const constantValue = '상수 값';
    console.log('const:', constantValue);
    //constantValue = '에러발생날껄?'; // 에러발생하는 문구 입니다., 이유는 const (ES6, 블록 스코프) - 재할당 불가합니다.

console.log('\n' + '='.repeat(50) + '\n');
//==================================================

console.log('2. 기본 데이터 타입:');

// Number 타입
const integer = 37; //정수
const float = 3.141592; //실수
const negative = -50;//음수
const infinity = Infinity;
const notANumber = NaN; 

console.log('Number:');
console.log('   정수 :', integer, 'Type:', typeof integer);
console.log('   실수 :', float, 'Type:', typeof float);
console.log('   음수 :', negative, 'Type:', typeof negative);
console.log('   무한대 :', infinity, 'Type:', typeof infinity);
console.log('   NaN :', notANumber, 'Type:', typeof notANumber);

// String 타입
const singleQuote = '작은 따옴표';
const doubleQuote = "큰따옴표";
const templateLiteral = `템플릿 리터럴 : ${integer} + ${float} = ${integer + float}`;
    
console.log('\nString 타입들:');
console.log('   작은따옴표:', singleQuote);
console.log('   큰따옴표:', doubleQuote);
console.log('   templateLiteral', templateLiteral);
    //templateLiteral 템플릿 리터럴 : 37 + 3.141592 = 40.141592

//Boolean 타입

const isTrue = true;
const isFalse = false;

console.log('\nBoolean 타입들:');
console.log('   true:', isTrue, '타입:', typeof isTrue);
console.log('   false:', isFalse, '타입:', typeof isFalse);

//Undefined 타입
let undefinedVariable;
console.log('\nUndefine 타입:');
console.log('   선언만 한 변수:', undefinedVariable);

//Null 타입
const nullValue = null;
console.log('\nNull Type:');
console.log('   null 값:', nullValue, '타입:', typeof nullValue);

//Symbol
const uniqueSymbol = Symbol('id');
console.log('Symbol Type:', uniqueSymbol, 'Type:', typeof uniqueSymbol);
/*
* Symbol은 객체가 아니라 변경 불가능한 원시 타입의 값
* Symbol() 함수는 String, Number, Boolean과 같이 래퍼 객체를 생성하는 생성자 함수와는 달리 new 연산자를 사용하지 않음
* 출처: https://inpa.tistory.com/entry/JS-📚-자료형-Symbol-🚩-정리 [Inpa Dev 👨‍💻:티스토리]
*/

//BigInt
const bigIntNum = 123456789012234213445678901234567890n;
console.log('BigInt Type:', bigIntNum, 'Type:', typeof bigIntNum);

console.log('\n' + '='.repeat(50) + '\n');
//==================================================

console.log('3. 참조 데이터 타입:');

const person = {
    name : 'glory',
    age : 32,
    grade : false,
    etc : ['keti','js']
};

console.log(person)
console.log('object 타입:');
console.log('   객체:', person);
console.log('   객체 type:', typeof person);
console.log('   속성 접근:', person.name);
console.log('   대괄호 접근:', person['age']);

const numbers = [1,2,4,8,6];
const mixed = [1, '문자열', true, {key: 'value'}];

console.log('\nArray Type:');
console.log('   숫자 배열:', numbers, 'Type:', typeof numbers);
console.log('   혼합 배열', mixed, '타입:', typeof mixed);
console.log('   배열 길이', numbers.length);
console.log('   첫 번째 요소:', numbers[0]);

//Function 타입
function greet(name) {
    return `안녕하세요, ${name}씨!!!`;
}

const arrowFunction = (name) => `Hello :), ${name}!!!!!!!`;

console.log('\nFunciton 타입:');
console.log('   Normal Function:', greet('철수'));
console.log('   Arrow Function:', arrowFunction('영희'));
console.log('   function Type:', typeof greet);

console.log('\n' + '='.repeat(50) + '\n');

// 4. 타입 반환 (Type Coercion)
console.log('4. 타입 변환 (Type Coercion):');

console.log('암시적 타입변환:');
console.log('  "4" + 1 =', "4" + 1); // ㅋㅋㅋㅋㅋ 어지럽네, 문자열 연결이라고 한다.
console.log('  "5" - 3 =', "5" - 3); // 숫자 연산
console.log('  "5" * "3" =', "5" * "3"); // 숫자 연산
console.log('  "5" / "3" =', "5" / "3"); // 숫자 연산
console.log('  true + 1 =', true + 1); // true는 1로 변환
console.log('  false + 1 =', false + 1); // false는 0으로 변환

// 명시적 타입 변환
console.log('\n명시적 타입변환:');
console.log('   String(123) = ', String(123), '타입:', typeof String(123));
console.log('   Number("13423") = ', Number("123"), '타입:', typeof Number("123"));
console.log('   Boolean(1) =', Boolean(1), '타입:', typeof Boolean(1));
console.log('   Boolean(0) =', Boolean(0), '타입:', typeof Boolean(0));
console.log('   Boolean("") =', Boolean(""), '타입', typeof Boolean(""));

console.log('\n' + '='.repeat(50) + '\n');

// 5.스코프 (Scope)
console.log('5. 스코프 (Scope)');

// 전역 스코프
const globalVar = '전역변수';

function scopeExample() {
    //함수 스코프
    const functionVar = '함수 내부 변수';
    console.log('   함수 내부에서 전역 변수 접근:', globalVar);
    console.log('   함수 내부 변수:', functionVar);

    if (true) {
        //블록스코프
        const blockVar = '블록 내부 변수';
        console.log('   블록 내부에서 함수 변수 접근:', functionVar);
        console.log('   블록 내부 변수:', blockVar);
    }

    // console.log(blockVar); // Error! 블록 외부에서 접근 불가
}

scopeExample();
console.log('   전역에서 전역 변수 접근하고 있는 중:', globalVar);
// console.log(functionVar); // 에러! 함수 외부에서 접근 불가

console.log('\n' + '='.repeat(50) + '\n');

// 6. 호이스팅 (Hoisting)
console.log('6. 호이스팅 (Hoisting):');

console.log('  var 호이스팅 - 선언 전 접근:', hoistedVar); // undefined
var hoistedVar = '호이스팅된 변수';

// console.log(hoistedLet); // 에러! let은 호이스팅되지 않음
let hoistedLet = '호이스팅되지 않는 변수';

console.log('\n=== 예제 완료 ===');
console.log('\n💡 학습 포인트:');
console.log('1. let과 const는 블록 스코프, var는 함수 스코프');
console.log('2. const는 재할당 불가, let은 재할당 가능');
console.log('3. JavaScript는 동적 타입 언어');
console.log('4. 타입 변환은 암시적/명시적으로 발생');
console.log('5. 호이스팅은 var에서만 발생'); 