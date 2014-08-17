import java.math.*;
import java.io.*;
import java.util.*;

public class Main {
	static fraction f[][];
	public static void main(String[] args){
		Scanner cin=new Scanner(new BufferedInputStream(System.in));
		int n=cin.nextInt();
		f=new fraction[n][n];
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				f[i][j]=new fraction(BigInteger.valueOf(cin.nextInt()), BigInteger.ONE);
		Matrix A = new Matrix(f);
		A.transpose();
		Matrix inv = A.invert();
		if(inv!=null){
			boolean flag=false;
			for(int i=0; i<inv.data.length; i++){
				for(int j=0; j<inv.data[i].length; j++){
					if(!inv.data[i][j].den.equals(BigInteger.ONE)){
						flag=true;
					}
				}
			}
			if(flag)System.out.println("Power of magic saves lives");
			else System.out.println("Death");
			//inv.print();
		} else System.out.println("Power of magic saves lives");
		cin.close();
	}
}

class fraction {
	public BigInteger num, den; //numerator & denominator
	static public final fraction ONE=new fraction(BigInteger.ONE, BigInteger.ONE);
	static public final fraction ZERO= new fraction(BigInteger.ZERO, BigInteger.ONE);
	public fraction(BigInteger _num, BigInteger _den){
		num=_num;
		den=_den;
		if(den.signum()==0){
			throw new IllegalArgumentException("Argument 'denominator' is 0");
		}
		fix();
	}
	public fraction add(fraction x){
		BigInteger gcd=den.gcd(x.den);
		BigInteger A=x.den, B=den;
		if(!gcd.equals(BigInteger.ONE)){
			A=A.divide(gcd);
			B=B.divide(gcd);
		}
		BigInteger newNum=num.multiply(A).add(x.num.multiply(B));
		BigInteger newDen=den.multiply(A);
		fraction t=new fraction(newNum, newDen);
		t.fix();
		return t;
	}
	public fraction negate(){return new fraction(num.negate(),den);}
	public fraction subtract(fraction x){return this.add(x.negate());}
	public fraction multiply(fraction x){
		BigInteger g1=num.gcd(x.den);
		BigInteger g2=den.gcd(x.num);
		fraction t=new fraction(num.divide(g1).multiply(x.num.divide(g2)), den.divide(g2).multiply(x.den.divide(g1)));
		return t;
	}
	fraction reciprocal(){
		if(num.signum()==0)return null; //divided by zero
		else return new fraction(den, num);
	}
	public fraction divide(fraction x){
		return this.multiply(x.reciprocal());
	}
	private void fix(){
		BigInteger gcd=num.gcd(den);
		if(gcd.compareTo(BigInteger.ONE)>0){
			num=num.divide(gcd);
			den=den.divide(gcd);
		}
		if(den.signum()<0){
			num=num.negate();
			den=den.negate();
		}
	}
	public int signum(){
		return num.signum();
	}
	public String toString(){
		String res=num.toString();
		if(den.compareTo(BigInteger.ONE)!=0)res+="/"+den.toString();
		return res;
	}
}
class Matrix {
	fraction[][] data;
	Matrix(fraction[][] _data){data=_data;}
	Matrix(int n, int m, int type){
		data=new fraction[n][m];
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				data[i][j]=fraction.ZERO;
		if(type==1){
			int nn=n<m?n:m;
			for(int i=0; i<nn; i++)
				data[i][i]=fraction.ONE;
		}
	}
	public void print(){
		for(int i=0; i<data.length; i++){
			for(int j=0; j<data[i].length; j++){
				System.out.printf("%5s ",data[i][j].toString());
			}
			System.out.println();
		}
	}
	boolean isSquare(){
		if(data.length==0)return true;
		else if(data.length==data[0].length)return true;
		else return false;
	}
	boolean transpose(){
		if(!isSquare())return false;
		for(int i=0; i<data.length; i++)
			for(int j=i+1; j<data[0].length; j++){
				fraction tmp=data[i][j];
				data[i][j]=data[j][i];
				data[j][i]=tmp;
			}
		return true;
	}
	void swapRow(int i, int j){
		fraction[] t=data[i];
		data[i]=data[j];
		data[j]=t;
	}
	void mulRow(int i, fraction time){
		if(time.signum()==0)return;
		for(int j=0; j<data[i].length; j++)
			data[i][j]=data[i][j].multiply(time);
	}
	void addMulRow(int i, int j, fraction time){
		if(time.signum()==0)return;
		for(int k=0; k<data[i].length; k++)
			data[j][k]=data[j][k].add(data[i][k].multiply(time));
	}
	Matrix invert(){
		if(!isSquare())return null;
		int n=data.length;
		Matrix M=new Matrix(n,n,1);
		for(int k=0; k<n; k++){
			int row=-1;
			for(int i=k; i<n; i++)
				if(data[i][k].signum()!=0){
					row=i;
					break;
				}
			if(row==-1)return null;
			swapRow(k, row);
			M.swapRow(k, row);
			fraction v=fraction.ONE.divide(data[k][k]);
			for(int i=0; i<n; i++){
				if(i==k)continue;
				fraction t=data[i][k].negate().multiply(v);
				addMulRow(k, i, t);
				M.addMulRow(k, i, t);
			}
			mulRow(k, v);
			M.mulRow(k, v);
		}
		return M;
	}
}