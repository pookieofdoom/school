
public class mb_hdr {

	public char signature[] = new char[4];
	public long size;
	public long entry;
	public long filler1;
	public char filler2[] = new char[64-16];
}
