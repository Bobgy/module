import java.math.*;

public class fraction {
	public BigInteger num, den;
	static public final fraction ONE=new fraction(BigInteger.ONE, BigInteger.ONE);
	fraction(BigInteger _num, BigInteger _den){num=_num;den=_den;} //用此方法构造的时候传入的量不能在别的地方被使用
	public fraction add(fraction x){
		BigInteger gcd=den.gcd(x.den);
		BigInteger A=x.den.divide(gcd);
		BigInteger B=den.divide(gcd);
		BigInteger newNum=num.multiply(A).add(x.num.multiply(B));
		BigInteger newDen=den.multiply(A);
		fraction t=new fraction(newNum, newDen);
		t.fix();
		return t;
	}
	public fraction negate(){return new fraction(num.negate(),den.add(BigInteger.ZERO));}
	public fraction subtract(fraction x){return this.add(x.negate());}
	public fraction multiply(fraction x){
		fraction t=new fraction(x.num.multiply(num), x.den.multiply(den));
		t.fix(); return t;
	}
	public fraction divide(fraction x){
		fraction t=new fraction(x.den.multiply(num), x.num.multiply(den));
		t.fix(); return t;
	}
	private void fix(){
		BigInteger gcd=num.gcd(den);
		if(gcd.compareTo(BigInteger.ONE)>0){
			num=num.divide(gcd);
			den=den.divide(gcd);
		}
		if(den.compareTo(BigInteger.ZERO)<0){
			num=num.negate();
			den=den.negate();
		}
	}
	public String toString(){
		String res=num.toString();
		if(den.compareTo(BigInteger.ONE)!=0)res+="/"+den.toString();
		return res;
	}
}
