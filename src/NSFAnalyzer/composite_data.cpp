#include "stdafx.h"
#include "search_core.h"

using namespace System::Runtime::InteropServices;
using namespace Windows::Forms;

/************************************************************************

    FUNCTION:   DumpOneCDRecord

    PURPOSE:    Dump one Compound Text (CD) Record

    ALGORITHM:  This is the action routine for EnumCompositeBuffer
		specified in DumpOneItem().

    INPUTS:
	 char      *RecordPtr       -   pointer to start of CD record data
					This data is in Canonical format.
	 WORD       RecordType      -   CD record type (SIG_CD_*)
	 DWORD      RecordLength    -   length of CD record
	 void far * Unused

*************************************************************************/
STATUS LNPUBLIC DumpOneCDRecord(char *RecordPtr, WORD RecordType, DWORD RecordLength, void *ptr)
{
    switch (RecordType) {
	case SIG_CD_PARAGRAPH:
	    DumpCDParagraph( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_PABDEFINITION:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_PABREFERENCE:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_TEXT:
    case SIG_CD_BIDI_TEXT: /* New for R5.0 */
	    DumpCDText( RecordPtr, RecordLength, RecordType, ptr );
	    break;

	case SIG_CD_HEADER:
	    DumpCDHeader( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_LINKEXPORT2:
	    DumpCDLinkexport2( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_BITMAPHEADER:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_BITMAPSEGMENT:
	    DumpCDBitmapsegment( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_COLORTABLE:
	    DumpCDColortable( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_GRAPHIC:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_PMMETASEG:
	    DumpCDPmmetaseg( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_WINMETASEG:
	    DumpCDWinmetaseg( RecordPtr, RecordLength , ptr);
	    break;

	case SIG_CD_MACMETASEG:
	    DumpCDMacmetaseg( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_CGMMETA:
	    DumpCDCgmmeta( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_PMMETAHEADER:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_WINMETAHEADER:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_MACMETAHEADER:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_TABLEBEGIN:
	case SIG_CD_NESTEDTABLEBEGIN: /* New for R5.0 */
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_TABLECELL:
	case SIG_CD_NESTEDTABLECELL:  /* New for R5.0 */
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_TABLEEND:
	case SIG_CD_NESTEDTABLEEND:   /* New for R5.0 */
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_STYLENAME:
	    DumpCDStylename( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_FIELD_PRE_36:
	    DumpCDField( RecordPtr, RecordLength, RecordType, ptr );
	    break;

	case SIG_CD_FIELD:
	    DumpCDField( RecordPtr, RecordLength, RecordType, ptr );
	    break;

	case SIG_CD_DOCUMENT:
	    DumpCDDocument( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_METAFILE:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_BITMAP:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_FONTTABLE:
		// structure contains no 'human' scannable elements		
	    break;

	case SIG_CD_LINK:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_LINKEXPORT:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_KEYWORD:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_LINK2:
	    DumpCDLink2( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_CGM:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_TIFF:
		// structure contains no 'human' scannable elements		
	    break;

	case SIG_CD_PATTERNTABLE:
	    DumpCDPatterntable( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_DDEBEGIN:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_DDEEND:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_OLEBEGIN:
	    DumpCDOlebegin( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_OLEEND:
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_HOTSPOTBEGIN:
	case SIG_CD_V4HOTSPOTBEGIN: /* New for R4.0 */
	case SIG_CD_V5HOTSPOTBEGIN: /* New for R5.0 */
	case SIG_CD_V6HOTSPOTBEGIN_CONTINUATION: /* New for Notes/Domino 6 */
	    DumpCDHotspotbegin( RecordPtr, RecordLength, RecordType, ptr );
	    break;

	case SIG_CD_HOTSPOTEND:
	case SIG_CD_V4HOTSPOTEND: /* New for R4.0 */
	case SIG_CD_V5HOTSPOTEND: /* New for R5.0 */
		// structure contains no 'human' scannable elements
	    break;

	case SIG_CD_BUTTON:
	    DumpCDButton( RecordPtr, RecordLength, ptr );
	    break;

		/* Records added in Release 4.0 */
	case SIG_CD_BAR:
		DumpCDBar( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_EXT_FIELD:
		DumpCDExtfield( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_PABHIDE:
		DumpCDPabhide( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_PABFORMREF:
		// structure contains no 'human' scannable elements
		break;

		/* Records added in Release 4.5 */
	case SIG_CD_LAYOUT:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_LAYOUTEND:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_LAYOUTTEXT:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_LAYOUTFIELD:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_LAYOUTGRAPHIC:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_LAYOUTBUTTON:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_TEXTEFFECT:
	case SIG_CD_BIDI_TEXTEFFECT:  /* New for R5.0 */
		DumpCDTextEffect( RecordPtr, RecordLength, RecordType, ptr );
		break;

	case SIG_CD_TRANSPARENTTABLE:
		DumpCDTransparentTable( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_STORAGELINK:
		DumpCDStorageLink( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_ACTION:
		DumpCDAction(RecordPtr, RecordLength, ptr);
		break;

	case SIG_CD_ACTIONBAR:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_DOCAUTOLAUNCH:
		DumpCDDocautolaunch( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_OLEOBJINFO:
		DumpCDOleObjInfo( RecordPtr, RecordLength, ptr );
		break;

		/* Records added in Release 4.6 */
	case SIG_CD_ANCHOR:
		DumpCDAnchor( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_ALTTEXT:
	case SIG_CD_HTML_ALTTEXT: /* New for R5.0 */
		DumpCDAltText( RecordPtr, RecordLength, RecordType, ptr );
		break;

	case SIG_CD_OLERTMARKER:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_ALTERNATEBEGIN:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_ALTERNATEEND:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_HORIZONTALRULE:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_HTMLBEGIN:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_HTMLEND:
		// structure contains no 'human' scannable elements		
		break;

	case SIG_CD_HTMLFORMULA:
		DumpCDHtmlFormula( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_HTMLHEADER:		
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_HTMLSEGMENT:
		DumpCDHtmlSegment( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_LSOBJECT:
		// structure contains no 'human' scannable elements
		break;

	/* Records added in R5.0 */
	case SIG_CD_COLOR:
	case SIG_CD_TABLECELL_COLOR:
	case SIG_CD_BACKGROUNDCOLOR:  /* New for Notes/Domino 6 */
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_BEGIN:
		// structure contains no 'human' scannable elements		
		break;

	case SIG_CD_END:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_VERTICALALIGN:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_FLOATPOSITION:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_TIMERINFO:		
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_TABLEROWHEIGHT:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_TABLELABEL:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_REGIONBEGIN:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_REGIONEND:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_TRANSITION:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_EMBEDDEDOUTLINE:
		DumpCDEmbeddedOutline( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_EMBEDDEDVIEW:
		DumpCDEmbeddedView( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_CELLBACKGROUNDDATA:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_TARGET:
		DumpCDTarget( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_MAPELEMENT:
		DumpCDMapElement( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_AREAELEMENT:
		// structure contains no 'human' scannable elements
		break;

	case SIG_CD_HREF:
	case SIG_CD_TABLECELL_HREF:
	case SIG_CD_HREF2: /* New for Notes/Domino 6 */
	case SIG_CD_HREFBORDER: /* New for Notes/Domino 6 */
	case SIG_CD_TABLECELL_HREF2: /* New for Notes/Domino 6 */
		DumpCDResource( RecordPtr, RecordLength, RecordType, ptr );
		break;

	case SIG_CD_EMBEDDEDCTL:
		// structure contains no 'human' scannable elements		
		break;

	case SIG_CD_EVENT:
	case SIG_CD_CLIENT_EVENT: /* New for Notes/Domino 6 */
		DumpCDEvent( RecordPtr, RecordLength, RecordType, ptr );
		break;

	case SIG_CD_IDNAME:
	case SIG_CD_TABLECELL_IDNAME:
		DumpCDIDName( RecordPtr, RecordLength, RecordType, ptr );
		break;

	case SIG_CD_PRETABLEBEGIN:
		DumpCDPreTableBegin( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_BORDERINFO:
		// structure contains no 'human' scannable elements		
		break;

	case SIG_CD_EMBEDDEDSCHEDCTL:
		DumpCDEmbeddedSchedCtl( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_EXT2_FIELD:
		// i dont care about this. This includes notes client-only field settings
		// and use of the native os setting. We will not can this. If someone really needs this,
		// then I will can the few things you might care about, such as im group name.
		break;

	case SIG_CD_ACTIONBAREXT:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_IMAGESEGMENT:
		// I am not going to scan the image segment. We could... if you want to scan for
		// hidden hex messages in the image segment, email me and I can make this happen.
		// but really... if you have that need, then you probably don't need my help.
		// Or as you are driving the black van that is following me, 
		// just honk the horn and we can talk ;p
		break;

	case SIG_CD_IMAGEHEADER:
		//	c'mon, enough already. same as above
		break;

	case SIG_CD_BLOBPART:
	case SIG_CD_CLIENT_BLOBPART: /* new in Notes/Domino 6 */
		DumpCDBlobPart( RecordPtr, RecordLength, RecordType, ptr );
		break;

	case SIG_CD_PLACEHOLDER:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_LINKCOLORS:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_CAPTION:
		DumpCDCaption ( RecordPtr, RecordLength, ptr );
		break;

	/* Records added in Release 5.0.1 */
	case SIG_CD_FRAME:
		DumpCDFrame ( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_FRAMESET:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_FRAMESETHEADER:
		// structure contains no 'human' scannable elements	
		break;

	/* Records added in Notes/Domino 6 */

	case SIG_CD_ACTIONEXT:
		DumpCDActionExt( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_EXT_EMBEDDEDSCHED:
		DumpCDEmbeddedSchedCtlExtra( RecordPtr, RecordLength, ptr ); // ...and more embedded scheduler formulas...
		break;

	case SIG_CD_INLINE:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_EMBEDDEDCALCTL:
		DumpCDEmbeddedCalCtl( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_LAYER:
		// structure contains no 'human' scannable elements	
	    break;

	case SIG_CD_POSITIONING:
		// structure contains no 'human' scannable elements	
	    break;

	case SIG_CD_BOXSIZE:
		// structure contains no 'human' scannable elements	
	    break;

	case SIG_CD_BACKGROUNDPROPERTIES:
		// structure contains no 'human' scannable elements	
	    break;

	case SIG_CD_EVENT_LANGUAGE_ENTRY:
		// structure contains no 'human' scannable elements	
	    break;
	
	case SIG_CD_TEXTPROPERTIESTABLE:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_FILEHEADER:
	    DumpCDFileHeader( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_FILESEGMENT:
		// structure contains no 'human' scannable elements	
	    break;

	case SIG_CD_DECSFIELD:
	    DumpCDDECSField( RecordPtr, RecordLength, ptr );
	    break;

	case SIG_CD_SPAN_BEGIN:
	case SIG_CD_SPAN_END:
		// structure contains no 'human' scannable elements	
	    break;

	case SIG_CD_EMBEDDEDEDITCTL:
		DumpCDEmbeddedEditCtl( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_TEXTPROPERTY:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_DATAFLAGS:
		// structure contains no 'human' scannable elements	
		break;

	 case SIG_CD_TABLECELL_DATAFLAGS:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_FIELDHINT:
		DumpCDFieldHint ( RecordPtr, RecordLength, ptr );
		break;

	case SIG_CD_LARGE_PARAGRAPH:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_TABLEDATAEXTENSION:
		//	Structure has little useful info to scan. The comments in the API causes me to prefer to avoid scanning this structure.
		break;

	case SIG_CD_IGNORE:
		// structure contains no 'human' scannable elements	
		break;

	case SIG_CD_EMBEDDEDCONTACTLIST:
		// structure contains no 'human' scannable elements	
		break;

   case SIG_CD_EMBEDEXTRA_INFO:
		DumpCDEmbedExtraInfo ( RecordPtr, RecordLength, ptr );
		break;

	default:
		GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
		NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

		scan_engine->WriteLog("Unknown CD type. RecordType=" + RecordType + 
						" (" + String::Format("{0,10:X}", RecordType) + "). NoteID=" + 
						scan_engine->scanner->SearchQuery->NoteID + ". Item=" + 
						scan_engine->scanner->SearchQuery->FieldName, true);
		
	    NSFDDUMPDumpMemory( RecordPtr, (WORD) RecordLength, ptr );

	    break;
   }
   return NOERROR;
}

/************************************************************************

    FUNCTION:   DumpCompoundTextItem

*************************************************************************/
void LNPUBLIC DumpCompoundTextItem(char *Name, WORD NameLength, char *pData, WORD length, void *pScan )
{
	PrintCompositeBuffer( pData, length, DumpOneCDRecord, pScan );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDParagraph

*************************************************************************/
void LNPUBLIC DumpCDParagraph(char *RecordPtr, DWORD RecordLength, void *ptr)
{
	// do nothing here. Perhaps log it eventually.
    return;
}

/************************************************************************

    FUNCTION:   DumpCDText

*************************************************************************/
void LNPUBLIC DumpCDText(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
    CDTEXT        cdt;
    char far *    p = RecordPtr;
    DWORD         dwLen;

	NSFAnalyzerEngine::pODSReadMemory (&p, _CDTEXT, &cdt, 1);
    
	dwLen = RecordLength - (DWORD)NSFAnalyzerEngine::pODSLength(_CDTEXT) ;
    if (dwLen > 0) {			
		PrintText( p, dwLen, ptr, "CD::Text" );	
    }

    return;
}

/************************************************************************

    FUNCTION:   DumpCDAction

*************************************************************************/
void LNPUBLIC DumpCDAction(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *          p = RecordPtr;
    CDACTION            cdAction;
	DWORD               dataLen;
	
	NSFAnalyzerEngine::pODSReadMemory(&p, _CDACTION, &cdAction, 1);

	if (0 != cdAction.TitleLen)
	{
		PrintText ((char far *) p, cdAction.TitleLen, ptr);
		p = ((char far *) p) + cdAction.TitleLen + (1 & cdAction.TitleLen);
								/* Account for any padding */
	}

	dataLen = RecordLength - NSFAnalyzerEngine::pODSLength (_CDACTION) - cdAction.TitleLen 
				- (1 & cdAction.TitleLen) - cdAction.FormulaLen - (1 & cdAction.FormulaLen);
	
	switch (cdAction.Type)
	{
		case ACTION_RUN_FORMULA:                /* Contains a formula */			
			PrintFormula (p, (WORD) dataLen, ptr, "CD::ACTION::RUN_FORMULA");
			break;

		case ACTION_RUN_SCRIPT:                 /* Contains Lotus Script */	
			PrintScriptSource (p, dataLen, ptr, "CD::ACTION::RUN_SCRIPT");
			break;
		case ACTION_RUN_JAVASCRIPT:			
			PrintText( p, (WORD) dataLen, ptr, "CD::ACTION::RUN_JAVASCRIPT" );
			break;
		case ACTION_RUN_AGENT:                  /* Contains Action records */			
			PrintNotesActions (p, dataLen, ptr, "CD::ACTION::RUN_JAVASCRIPT");
			break;

		case ACTION_OLDSYS_COMMAND:             /* Old command codes */
		case ACTION_SYS_COMMAND:                /* New command codes */			
			break;			

		case ACTION_PLACEHOLDER:                /* Placeholder (???) */
			break;

		default:                /* Unknown code */
			break;
	}

	p = ((char far *) p) + dataLen;

	if ((0 != cdAction.FormulaLen) && (0 == (cdAction.Flags & ACTION_NO_FORMULA))) {		
		PrintFormula (p, cdAction.FormulaLen, ptr, "CD::ACTION::NO_FORMULA");
		p = ((char far *) p) + cdAction.FormulaLen + (1 & cdAction.FormulaLen);
								/* Account for any padding */
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDHeader

*************************************************************************/
void LNPUBLIC DumpCDHeader(char *RecordPtr, DWORD RecordLength, void *ptr ) {
    CDHEADER      cdhdr;
    char far *    p = RecordPtr;
    WORD          wTextLen;
		
	NSFAnalyzerEngine::pODSReadMemory(&p, _CDHEADER, &cdhdr, 1);

	wTextLen = ((WORD)RecordLength) - NSFAnalyzerEngine::pODSLength(_CDHEADER);

	PrintText((char far *)p, (DWORD)wTextLen, ptr, "CD::Header");
}

/************************************************************************

    FUNCTION:   DumpCDLinkexport2

*************************************************************************/
void LNPUBLIC DumpCDLinkexport2(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *      p = RecordPtr;
    CDLINKEXPORT2   cdLinkExp2;
	DWORD           textLen;    
	
    NSFAnalyzerEngine::pODSReadMemory(&p, _CDLINKEXPORT2, &cdLinkExp2, 1 );

	PrintNOTELINK(&cdLinkExp2.NoteLink, ptr );

	textLen = RecordLength - (DWORD)NSFAnalyzerEngine::pODSLength(_CDLINKEXPORT2);
	if (textLen)
		PrintText( p, textLen, ptr, "CD::LinkExport2" ) ;

    return;
}

/************************************************************************

    FUNCTION:   DumpCDBitmapsegment

*************************************************************************/
void LNPUBLIC DumpCDBitmapsegment(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *			p = RecordPtr;
    CDBITMAPSEGMENT     cdBitmapSeg;

    NSFAnalyzerEngine::pODSReadMemory(&p, _CDBITMAPSEGMENT, &cdBitmapSeg, 1);

	NSFDDUMPDumpMemory( p, (WORD)(RecordLength-NSFAnalyzerEngine::pODSLength(_CDBITMAPSEGMENT)), ptr, "CD::BitmapSegment" );

	return;
}

/************************************************************************

    FUNCTION:   DumpCDField

    PURPOSE:    Dump either a CDFIELD record or a CDFIELD_PRE_36 record
		
    DESCRIPTION:
	This function handles both CDFIELD and CDFIELD_PRE_36 records
	because they share identical structure except for the text
	list of legal keyword values.  The third input parameter
	specifies which type of field is pointed to by RecordPtr.

	Call ODSReadMemory to convert the CDFIELD (or CDFIELD_PRE_36)
	structure from canonical format to host format, storing the
	result in cdField (or cdFieldPre36). This advances pointer p to
	the next byte in the canonical format buffer after the CDFIELD
	structure. This may be the start of the Default Value Formula,
	the Input Translation Formula, Input Validity Check Formula, or
	Item Name.

*************************************************************************/
void LNPUBLIC DumpCDField( char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
    char far *       p = RecordPtr;
    CDFIELD          cdField;
    CDFIELD_PRE_36   cdFieldPre36;
    WORD             wFieldFlags;
    WORD             wDataType;
    WORD             wInputListDelim;
    WORD             wDisplayListDelim;
    NFMT             NumberFormat;
    TFMT             TimeFormat;
    FONTID           FontID;
    WORD             NameLength;
    WORD             DescLength;
    WORD             TextValueLength;
	WORD             DVLength;              /* Length of Default Value formula */
	WORD             ITLength;              /* Length of Input Translation formula */
	WORD             IVLength;              /* Length of Input Validation formula */

	String ^ dtl = "CD::Field";
    if (RecordType == SIG_CD_FIELD) {
		// field
		NSFAnalyzerEngine::pODSReadMemory(&p, _CDFIELD, &cdField, 1);

		wFieldFlags       = cdField.Flags;
		wDataType         = cdField.DataType;
		wInputListDelim   = cdField.ListDelim & LD_MASK ;
		wDisplayListDelim = cdField.ListDelim & LDD_MASK ;
		NumberFormat      = cdField.NumberFormat;
		TimeFormat        = cdField.TimeFormat;
		FontID            = cdField.FontID;
		DVLength          = cdField.DVLength;
		ITLength          = cdField.ITLength;
		IVLength          = cdField.IVLength;
		NameLength        = cdField.NameLength;
		DescLength        = cdField.DescLength;
		TextValueLength   = cdField.TextValueLength;

    } else if (RecordType == SIG_CD_FIELD_PRE_36) {
		// pre 36 field

	NSFAnalyzerEngine::pODSReadMemory(&p, _CDFIELD_PRE_36, &cdFieldPre36, 1);
		wFieldFlags       = cdFieldPre36.Flags;
		wDataType         = cdFieldPre36.DataType;
		wInputListDelim   = cdFieldPre36.ListDelim & LD_MASK ;
		wDisplayListDelim = cdFieldPre36.ListDelim & LDD_MASK ;
		NumberFormat      = cdFieldPre36.NumberFormat;
		TimeFormat        = cdFieldPre36.TimeFormat;
		FontID            = cdFieldPre36.FontID;
		DVLength          = cdFieldPre36.DVLength;
		ITLength          = cdFieldPre36.ITLength;
		IVLength          = cdFieldPre36.IVLength;
		NameLength        = cdFieldPre36.NameLength;
		DescLength        = cdFieldPre36.DescLength;
		TextValueLength   = 0; /*is only in CDFIELD, not CDFIELD_PRE_36*/
		
		dtl += "::Pre36";
		
    } else { 
		/* should never get here */	
		GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
		NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

		scan_engine->WriteLog("Unknown cd field type. RecordType=" + RecordType + 
						" (" + String::Format("{0,10:X}", RecordType) + "). NoteID=" + 
						scan_engine->scanner->SearchQuery->NoteID + ". Item=" + 
						scan_engine->scanner->SearchQuery->FieldName, true);
		return;
    }
    
    /* Default Value Formula.*/
    if (DVLength>0) {			
		PrintFormula ( p, DVLength, ptr, dtl + "::Default Value" );

		/* advance p to the next byte after the compiled formula */
		p = (  ((char*)p) + DVLength  );
    }

    /* Input Translation Formula */
    if (ITLength>0) {
		PrintFormula ( p, ITLength, ptr, dtl + "::Input Translation Formula"  );

		/* advance p past the input translation formula */
		p = (  ((char *)p) + ITLength  );
    }

    /* Input Validation Formula */
    if (IVLength>0) {		
		PrintFormula ( p, IVLength, ptr, dtl + "::Input Validation Formula");

		/* advance p past the input validation formula */
		p = (  ((char *)p) + IVLength  );
    }

    /* Item Name */
	if (0 != NameLength){
		PrintText( (char far *)p, NameLength, ptr, dtl + "::Item Name");
		p = ( ((char far *)p) + NameLength );
	}

	if (0 != DescLength) {
		PrintText( (char far *)p, DescLength, ptr, dtl + "::Description" );
		p = ( ((char far *)p) + DescLength );
	}
	
    /* List of key word values */
    if ( (TextValueLength > 0) && (wFieldFlags & FKEYWORDS) ) {
		LIST  List;
		WORD *awLengths;
		WORD  i;
	
		NSFAnalyzerEngine::pODSReadMemory( &p, _LIST, (void *)&List, 1 );

			/* Is this a text list or a formula? */
		if (0 != List.ListEntries) {
				/* Number of entries is non-zero - it's a text list */
				/* allocate an array of length words */
			awLengths = (WORD*)calloc( List.ListEntries, sizeof(WORD) );

				/* populate the array with length words */
			if (awLengths != (WORD*)NULL) {
				NSFAnalyzerEngine::pODSReadMemory( &p, _WORD, (void *)awLengths, List.ListEntries );
				for (i = 0; i < List.ListEntries; i++) {			
					PrintText( p, awLengths[i], ptr, dtl + "::Text List");
					p = (  ((char far *)p) + awLengths[i]  );
				}
				free(awLengths);
			}
		} else {
				/* Number of entries is zero - it's a formula */			
			PrintFormula (p, (WORD) (TextValueLength - (WORD)NSFAnalyzerEngine::pODSLength (_WORD)), ptr, dtl + "::Formula");
		}
    }

    return;
}


/************************************************************************

    FUNCTION:   DumpCDDocument

*************************************************************************/
void LNPUBLIC DumpCDDocument( char *RecordPtr, DWORD RecordLength, void *ptr ) {
    char far *       p = RecordPtr;
    CDDOCUMENT       cdDocument;
	DWORD            textFieldNameLength;
	
    NSFAnalyzerEngine::pODSReadMemory( &p, _CDDOCUMENT, &cdDocument, 1 );

	textFieldNameLength = RecordLength - ((DWORD)NSFAnalyzerEngine::pODSLength(_CDDOCUMENT));

    if (cdDocument.FormFlags & TPL_FLAG_SPARESOK) {
		if (cdDocument.InherFieldNameLength) {
			PrintText( (char far *) p, (DWORD)cdDocument.InherFieldNameLength, ptr, "CD::Document::Inherited Field Name" );
			p = ((char far *) p) + cdDocument.InherFieldNameLength;
			textFieldNameLength -= cdDocument.InherFieldNameLength;
		}
    }
    
	if (textFieldNameLength) {
		PrintText ( (char far *) p, textFieldNameLength, ptr, "CD::Document::Field Name" );
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDLink2

*************************************************************************/
void LNPUBLIC DumpCDLink2( char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *  p = RecordPtr;
    CDLINK2     cdLink2;
	DWORD       dwLen;

    NSFAnalyzerEngine::pODSReadMemory( &p, _CDLINK2, &cdLink2, 1 );

    dwLen = RecordLength - (DWORD)NSFAnalyzerEngine::pODSLength(_CDLINK2) ;
    if (dwLen > 0) {
		PrintText( p, dwLen, ptr, "CD::Link2" );
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDPatterntable

*************************************************************************/
void LNPUBLIC DumpCDPatterntable(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *       p = RecordPtr;
    CDPATTERNTABLE   CDPatternTable;

    NSFAnalyzerEngine::pODSReadMemory( &p, _CDPATTERNTABLE, &CDPatternTable, 1 );
    
	NSFDDUMPDumpMemory( p, (WORD)(RecordLength-NSFAnalyzerEngine::pODSLength(_CDPATTERNTABLE)), ptr, "CD::Pattern Table" );    

    return;
}

/************************************************************************

    FUNCTION:   DumpCDOlebegin

*************************************************************************/

void LNPUBLIC DumpCDOlebegin(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *  p = RecordPtr;
	CDOLEBEGIN  cdOleBegin;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDOLEBEGIN, &cdOleBegin, 1);
	
	PrintText( (char far *)p, cdOleBegin.AttachNameLength, ptr, "CD::OLE Begin::Attachment Name" );
    p = ( ((char far *)p) + cdOleBegin.AttachNameLength );

	if (cdOleBegin.ClassNameLength)	{		
		PrintText( (char far *)p, cdOleBegin.ClassNameLength, ptr, "CD::OLE Begin::Class Name");
		p = ( ((char far *)p) + cdOleBegin.ClassNameLength );
	}

	if (cdOleBegin.TemplateNameLength) {		
		PrintText( (char far *)p, cdOleBegin.TemplateNameLength, ptr, "CD::OLE Begin::Template Name" );
		p = ( ((char far *)p) + cdOleBegin.TemplateNameLength );
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDHotspotbegin

*************************************************************************/
void LNPUBLIC DumpCDHotspotbegin(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
    char far *       p = RecordPtr;
    CDHOTSPOTBEGIN   cdHotSpot;
	char             *szHotSpotType;
    WORD             i;
    char             Unknown[] = "Unknown";

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	/* Hotspot type table moved to beginning of source file! */

	if (SIG_CD_HOTSPOTBEGIN == RecordType) {
	} else if (SIG_CD_V4HOTSPOTBEGIN == RecordType) {
	} else if (SIG_CD_V5HOTSPOTBEGIN == RecordType)	{
	} else if (SIG_CD_V6HOTSPOTBEGIN_CONTINUATION == RecordType) {
	} else {
		scan_engine->WriteLog("Unknown hotspot type. RecordType=" + RecordType + 
						" (" + String::Format("{0,10:X}", RecordType) + "). NoteID=" + 
						scan_engine->scanner->SearchQuery->NoteID + ". Item=" + 
						scan_engine->scanner->SearchQuery->FieldName, true);

		return;
	}

    NSFAnalyzerEngine::pODSReadMemory( &p, _CDHOTSPOTBEGIN, &cdHotSpot, 1 );

    for (i=0;i<NUM_HOTSPOT_TYPES;i++) {
		if(cdHotSpot.Type == HotSpotTypeTable[i].wHotSpotType) {
			szHotSpotType = HotSpotTypeTable[i].szTypeStr;
			break;
		}
    }
    if (i==NUM_HOTSPOT_TYPES) {
		szHotSpotType = Unknown;
    }
        
    if (cdHotSpot.DataLength==0)
		return;

		/* Figure out what kind of information is stored for this hotspot */
	if (HOTSPOTREC_TYPE_ACTIVEOBJECT == cdHotSpot.Type) {
		DumpActiveObject (p, cdHotSpot.DataLength, ptr);
	}
	else if (HOTSPOTREC_TYPE_OLERICHTEXT == cdHotSpot.Type) {
		DumpHSOleRichText (p, cdHotSpot.DataLength, ptr);
	}
	else if (cdHotSpot.Flags & HOTSPOTREC_RUNFLAG_ACTION) {
		PrintNotesActions (p, cdHotSpot.DataLength, ptr,"Hot Spot::Action");
	}
	else if (cdHotSpot.Flags & HOTSPOTREC_RUNFLAG_SCRIPT) {
			/* Print the Lotus Script source (if available) */
		PrintScriptSource (p, cdHotSpot.DataLength, ptr, "Hot Spot::LotusScript");
	}
    else if ((cdHotSpot.Flags & HOTSPOTREC_RUNFLAG_FORMULA)|| (cdHotSpot.Type == HOTSPOTREC_TYPE_BUTTON)) {
			/* Print the formula */
		PrintFormula ( p, cdHotSpot.DataLength, ptr, "Hot Spot::Formula or Button" );
	}
	else { /* data is text */    	
		PrintText( (char far *)p,  cdHotSpot.DataLength, ptr, "Hot Spot:Text" );
    }

    return;
}

/************************************************************************

    FUNCTION:   DumpCDBar

*************************************************************************/
void LNPUBLIC DumpCDBar(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *       p = RecordPtr;
    CDBAR            cdBar;
    DWORD            dwFlags;
	WORD             dataLen;

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	NSFAnalyzerEngine::pODSReadMemory (&p, _CDBAR, &cdBar, 1);
	dataLen = (WORD) RecordLength - NSFAnalyzerEngine::pODSLength (_CDBAR);
    dwFlags = cdBar.Flags;

	if (dwFlags & BARREC_HAS_COLOR) {
		WORD              color;

		NSFAnalyzerEngine::pODSReadMemory (&p, _WORD, &color, 1);
		dataLen -= NSFAnalyzerEngine::pODSLength(_WORD);
	}

	if (dwFlags & BARREC_ISFORMULA) {
		PrintFormula (p, dataLen, ptr, "CD::Action Bar (formula)");
		p = ((char FAR *) p) + dataLen;
	} else {
		PrintText ((char far *)p, dataLen, ptr, "CD::Action Bar (text)");
		p = ((char FAR *) p) + dataLen;
	}

	return;
}
/************************************************************************

    FUNCTION:   DumpCDColortable

*************************************************************************/
void LNPUBLIC DumpCDColortable(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *       p = RecordPtr;
    CDCOLORTABLE     CDColorTable;

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

    NSFAnalyzerEngine::pODSReadMemory( &p, _CDCOLORTABLE, &CDColorTable, 1 );

	NSFDDUMPDumpMemory( p, (WORD)(RecordLength-NSFAnalyzerEngine::pODSLength(_CDCOLORTABLE)), ptr, "CD::Color Table" );
    
    return;
}


/************************************************************************

    FUNCTION:   DumpCDPmmetaseg

*************************************************************************/
void LNPUBLIC DumpCDPmmetaseg(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *       p = RecordPtr;
    CDPMMETASEG      cdPMSeg;

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

    NSFAnalyzerEngine::pODSReadMemory( &p,  _CDPMMETASEG, &cdPMSeg, 1 );

	NSFDDUMPDumpMemory( p, (WORD)(RecordLength-NSFAnalyzerEngine::pODSLength(_CDPMMETASEG)), ptr, "CD::PM Metafile Segment");
    
    return;
}

/************************************************************************

    FUNCTION:   DumpCDPmmetaseg

*************************************************************************/
void LNPUBLIC DumpCDWinmetaseg(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *       p = RecordPtr;
    CDWINMETASEG     cdWINSeg;

    NSFAnalyzerEngine::pODSReadMemory( &p,  _CDWINMETASEG, &cdWINSeg, 1 );

	NSFDDUMPDumpMemory( p, (WORD)(RecordLength-NSFAnalyzerEngine::pODSLength(_CDWINMETASEG)), ptr, "CD::Win Metafile Segment");
    
    return;
}

/************************************************************************

    FUNCTION:   DumpCDMacmetaseg

*************************************************************************/
void LNPUBLIC DumpCDMacmetaseg (char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *       p = RecordPtr;
    CDMACMETASEG     cdMacSeg;

    NSFAnalyzerEngine::pODSReadMemory( &p, _CDMACMETASEG, &cdMacSeg, 1 );    
	
	NSFDDUMPDumpMemory( p, (WORD)(RecordLength-NSFAnalyzerEngine::pODSLength(_CDMACMETASEG)), ptr, "CD::Mac Metafile Segment");
    
    return;
}


/************************************************************************

    FUNCTION:   DumpCDMacmetaseg

*************************************************************************/
void LNPUBLIC DumpCDCgmmeta (char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *       p = RecordPtr;
    CDCGMMETA        cdCGMSeg;

    NSFAnalyzerEngine::pODSReadMemory( &p, _CDCGMMETA, &cdCGMSeg, 1 );    
	
	NSFDDUMPDumpMemory( p, (WORD)(RecordLength-NSFAnalyzerEngine::pODSLength(_CDCGMMETA)), ptr, "CD::CGM Metafile");
    
    return;
}


/************************************************************************

    FUNCTION:   DumpCDStylename

*************************************************************************/

void LNPUBLIC DumpCDStylename(char * RecordPtr, DWORD RecordLength, void *ptr) {
    char far *       p = RecordPtr;
    CDSTYLENAME      cdStyleName;

    NSFAnalyzerEngine::pODSReadMemory( &p, _CDSTYLENAME, &cdStyleName, 1 );

	if (STYLE_FLAG_FONTID & cdStyleName.Flags)
	{
			/* . . . read it! */
		p += sizeof (FONTID);
	}

		/* If this is a permanent style . . . */
	if (STYLE_FLAG_PERMANENT & cdStyleName.Flags) {
		WORD    userNameLen;

		/* Read the length of the user name */
		NSFAnalyzerEngine::pODSReadMemory ( &p, _WORD, &userNameLen, 1);
		PrintText (p, userNameLen, ptr, "CD::Style Name");
	}

	return;
}


/************************************************************************

    FUNCTION:   DumpCDButton

*************************************************************************/
void LNPUBLIC DumpCDButton(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *    p = RecordPtr;
    CDBUTTON      cdButton;    
    
    NSFAnalyzerEngine::pODSReadMemory( &p, _CDBUTTON, &cdButton, 1 );

	PrintText( (char far *)p, RecordLength - NSFAnalyzerEngine::pODSLength(_CDBUTTON), ptr, "CD::Button" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDAltText

*************************************************************************/
void LNPUBLIC DumpCDAltText (char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
    char far *                  p = RecordPtr;
    CDALTTEXT                   cdAltText;

    NSFAnalyzerEngine::pODSReadMemory(&p, _CDALTTEXT, &cdAltText, 1);

	PrintText (p, cdAltText.wLength, ptr, "CD::Alt Text");

    return;
}


/************************************************************************

    FUNCTION:   DumpCDExtfield

*************************************************************************/
void LNPUBLIC DumpCDExtfield(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *      p = RecordPtr;
    CDEXTFIELD      cdExtField;

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDEXTFIELD, &cdExtField, 1 );

	if (0 != cdExtField.EntryDBNameLen)
	{		
		PrintText( (char far *)p, cdExtField.EntryDBNameLen, ptr, "CD::Extended Field::Entry Database Name");
		p = ((char far *) p) + cdExtField.EntryDBNameLen;
	}

	if (0 != cdExtField.EntryViewNameLen)
	{
		PrintText( (char far *)p, cdExtField.EntryViewNameLen, ptr, "CD::Extended Field::Entry View Name");
		p = ((char far *) p) + cdExtField.EntryViewNameLen;
	}

		/* Is there an HTML formula following this record? */
	if (cdExtField.Flags2 & FEXT_HTML_IN_FIELDDEF)
	{
		WORD            htmlLength;
		WORD            wSpareFlags;
		WORD            wTrueLength;

		NSFAnalyzerEngine::pODSReadMemory (&p, _WORD, &htmlLength, 1);              /* Read the HTML formula length */
		NSFAnalyzerEngine::pODSReadMemory (&p, _WORD, &wSpareFlags, 1);             /* Read the spare flags word */

			/* If this field is edited by someone using a release of                 */
			/* Domino and Notes prior to 4.6, this record may be truncated.          */
		    /* If that happens, Domino and Notes ignores the (missing) HTML formula. */
		wTrueLength = NSFAnalyzerEngine::pODSLength (_CDEXTFIELD) + cdExtField.EntryDBNameLen
			+ cdExtField.EntryViewNameLen + (2 * NSFAnalyzerEngine::pODSLength (_WORD)) + htmlLength;

		if (wTrueLength > cdExtField.Header.Length) {
			scan_engine->WriteLog("Record overwritten by Notes prior to 4.6. HTML formula was lost.", true);
		} else {
			PrintFormula (p, htmlLength, ptr, "CD::Extended Field::HTML in Field Definition");
			p = ((char far *) p) + htmlLength;
		}
	}

    return;
}
/************************************************************************

    FUNCTION:   DumpCDPabhide

*************************************************************************/
void LNPUBLIC DumpCDPabhide(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *      p = RecordPtr;
    CDPABHIDE       cdPABHide;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDPABHIDE, &cdPABHide, 1 );

	/* Decompile and print the Hide When formula */
	PrintFormula ( p, ((WORD) (RecordLength - NSFAnalyzerEngine::pODSLength(_CDPABHIDE))), ptr, "CD::Paragraph HW Formula" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDTextEffect

*************************************************************************/
void LNPUBLIC DumpCDTextEffect(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
    char far *          p = RecordPtr;
    CDTEXTEFFECT        cdTextEffect;
    DWORD               dwLen;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDTEXTEFFECT, &cdTextEffect, 1);

    dwLen = RecordLength - (DWORD) NSFAnalyzerEngine::pODSLength(_CDTEXTEFFECT);
    if (dwLen > 0) {
		PrintText (p, dwLen, ptr, "CD::Text Effect");
    }

    return;
}

/************************************************************************

    FUNCTION:   DumpCDTransparentTable

*************************************************************************/
void LNPUBLIC DumpCDTransparentTable(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *          p = RecordPtr;
    CDTRANSPARENTTABLE  cdTransparentTable;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDTRANSPARENTTABLE, &cdTransparentTable, 1);

	NSFDDUMPDumpMemory (p, (WORD)(RecordLength-NSFAnalyzerEngine::pODSLength(_CDCOLORTABLE)), ptr, "CD::Transparent Table");    

    return;
}

/************************************************************************

    FUNCTION:   DumpCDStorageLink

*************************************************************************/
void LNPUBLIC DumpCDStorageLink(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *          p = RecordPtr;
    CDSTORAGELINK       cdStorageLink;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDSTORAGELINK, &cdStorageLink, 1);

	switch (cdStorageLink.StorageType)
	{
		case STORAGE_LINK_TYPE_OBJECT:
		case STORAGE_LINK_TYPE_URL_CONVERTED:
		case STORAGE_LINK_TYPE_URL_MIME:
			PrintText (p, cdStorageLink.DataLength, ptr, "CD::Storage Link:: URL MIME");
			break;

		default:
			NSFDDUMPDumpMemory (p, cdStorageLink.DataLength, ptr, "CD::Storage Link::Unknown");
			break;
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDDocautolaunch

*************************************************************************/
void LNPUBLIC DumpCDDocautolaunch(char * RecordPtr, DWORD RecordLength, void *ptr) {
    char far *                  p = RecordPtr;
    CDDOCAUTOLAUNCH             cdDocAutoLaunch;

    NSFAnalyzerEngine::pODSReadMemory(&p, _CDDOCAUTOLAUNCH, &cdDocAutoLaunch, 1);

	if (0 != cdDocAutoLaunch.FieldNameLength)
	{
		PrintText ((char far *) p, cdDocAutoLaunch.FieldNameLength, ptr, "CD::Document Auto Launch::Field Name");
		p = ((char far *) p) + cdDocAutoLaunch.FieldNameLength;
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDOleObjInfo

*************************************************************************/
void LNPUBLIC DumpCDOleObjInfo( char * RecordPtr, DWORD RecordLength, void *ptr ) {

	char far *          p = RecordPtr;
    CDOLEOBJ_INFO       cdOleObjInfo;

	NSFAnalyzerEngine::pODSReadMemory (&p, _CDOLEOBJ_INFO, &cdOleObjInfo, 1);

	if (0 != cdOleObjInfo.FileObjNameLength) {
		PrintText ((char far *) p, cdOleObjInfo.FileObjNameLength, ptr, "CD::OLE Object Info::File Object Name");
		p = ((char far *) p) + cdOleObjInfo.FileObjNameLength;
	}

	if (0 != cdOleObjInfo.DescriptionNameLength) {		
		PrintText ((char far *) p, cdOleObjInfo.DescriptionNameLength, ptr, "CD::OLE Object Info::Description Name");
		p = ((char far *) p) + cdOleObjInfo.DescriptionNameLength;
	}

	if (0 != cdOleObjInfo.FieldNameLength) {
		PrintText ((char far *) p, cdOleObjInfo.FieldNameLength, ptr, "CD::OLE Object Info::Field Name");
		p = ((char far *) p) + cdOleObjInfo.FieldNameLength;
	}

	if (0 != cdOleObjInfo.TextIndexObjNameLength) {
		PrintText ((char far *) p, cdOleObjInfo.TextIndexObjNameLength, ptr, "CD::OLE Object Info::Text Index Object Name");
		p = ((char far *) p) + cdOleObjInfo.TextIndexObjNameLength;
	}

	if (0 != cdOleObjInfo.HTMLDataLength) {
		PrintText ((char far *) p, cdOleObjInfo.HTMLDataLength, ptr, "CD::OLE Object Info::HTML Data");
		p = ((char far *) p) + cdOleObjInfo.HTMLDataLength;
	}

	if (0 != cdOleObjInfo.AssociatedFILEsLength) {
		PrintText ((char far *) p, cdOleObjInfo.AssociatedFILEsLength, ptr, "CD::OLE Object Info::Associated File");
		p = ((char far *) p) + cdOleObjInfo.AssociatedFILEsLength;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDAnchor

*************************************************************************/
void LNPUBLIC DumpCDAnchor(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *                  p = RecordPtr;
    CDANCHOR                    cdAnchor;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDANCHOR, &cdAnchor, 1);

		/* Print the anchor text */
	PrintText (p, cdAnchor.Datalength, ptr, "CD::Anchor");

    return;
}

/************************************************************************

    FUNCTION:   DumpCDHtmlFormula

*************************************************************************/
void LNPUBLIC DumpCDHtmlFormula (char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *                  p = RecordPtr;
    CDHTMLFORMULA               cdHtmlFormula;
	WORD                        dataLen;

	NSFAnalyzerEngine::pODSReadMemory (&p, _CDHTMLFORMULA, &cdHtmlFormula, 1);

	dataLen = (WORD) (RecordLength - NSFAnalyzerEngine::pODSLength (_CDHTMLFORMULA));
	
	if (0 != dataLen){
		NSFDDUMPDumpMemory (p, dataLen, ptr, "CD::Html Formula");
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDHtmlSegment

*************************************************************************/
void LNPUBLIC DumpCDHtmlSegment (char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *                  p = RecordPtr;
    CDHTMLSEGMENT               cdHtmlSegment;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDHTMLSEGMENT, &cdHtmlSegment, 1);

	PrintText (p, cdHtmlSegment.wHTMLLength, ptr, "CD::Html Segment");

	return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedOutline

*************************************************************************/
void LNPUBLIC DumpCDEmbeddedOutline (char *RecordPtr, DWORD RecordLength, void *ptr) {

	char far *			p = RecordPtr;
	CDEMBEDDEDOUTLINE	cdEmbeddedOutline;

	NSFAnalyzerEngine::pODSReadMemory (&p, _CDEMBEDDEDOUTLINE, &cdEmbeddedOutline, 1);

	if( cdEmbeddedOutline.LabelLength > 0 ) {		
		PrintText(( char far *) p, (WORD)cdEmbeddedOutline.LabelLength, ptr, "CD::Embedded Outline::Label" );
		p = ((char far *) p) + cdEmbeddedOutline.LabelLength;
	}

	if(( cdEmbeddedOutline.NameLength > 0) && (cdEmbeddedOutline.Flags & EMBEDDEDOUTLINE_FLAG_HASNAME))	{	
		PrintText(( char far *) p, (WORD)cdEmbeddedOutline.NameLength, ptr, "CD::Embedded Outline::Name" );
		p = ((char far *) p) + cdEmbeddedOutline.NameLength;
	}
		
	if(( cdEmbeddedOutline.TargetFrameLength > 0 ) && ( cdEmbeddedOutline.Flags & EMBEDDEDOUTLINE_FLAG_HASTARGETFRAME )) {
		PrintText(( char far *) p, (WORD)cdEmbeddedOutline.TargetFrameLength, ptr, "CD::Embedded Outline::Target Frame" );
		p = ((char far *) p) + cdEmbeddedOutline.TargetFrameLength;
	}

	if(( cdEmbeddedOutline.RootLength > 0 ) && ( cdEmbeddedOutline.Flags & EMBEDDEDOUTLINE_FLAG_HASROOTNAME )) {
		PrintText(( char far *) p, (WORD)cdEmbeddedOutline.RootLength, ptr, "CD::Embedded Outline::Root Name" );
		p = ((char far *) p) + cdEmbeddedOutline.RootLength;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedView

*************************************************************************/
void LNPUBLIC DumpCDEmbeddedView(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *		p = RecordPtr;
	CDEMBEDDEDVIEW	cdEmbeddedView;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDEMBEDDEDVIEW, &cdEmbeddedView, 1 );

	/* Dump the Single Category Selection Formula */
	if( cdEmbeddedView.RestrictFormulaLength > 0) {
		PrintFormula( p, cdEmbeddedView.RestrictFormulaLength, ptr, "CD::Embedded View::Single Category Selection Formula" );
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDTarget

*************************************************************************/
void LNPUBLIC DumpCDTarget(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *	p = RecordPtr;
	CDTARGET	cdTarget;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDTARGET, &cdTarget, 1 ) ;

	if (cdTarget.TargetLength > 0) {
		if(cdTarget.Flags & FLAG_TARGET_IS_FORMULA)	{
			PrintFormula( p, cdTarget.TargetLength, ptr, "CD::Target::Formula" );
		} else {        
			PrintText (p, cdTarget.TargetLength, ptr, "CD::Target::Text");
		}
    }

	return;
}

/************************************************************************

    FUNCTION:   DumpCDMapElement

*************************************************************************/
void LNPUBLIC DumpCDMapElement(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *		p = RecordPtr;
	CDMAPELEMENT	cdMapElement;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDMAPELEMENT, &cdMapElement, 1 ) ;

	if( cdMapElement.MapNameLength > 0 ) {
		PrintText( p, cdMapElement.MapNameLength, ptr, "CD::Map Element::Map Name" );
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDResource

*************************************************************************/
void LNPUBLIC DumpCDResource(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
	char far *	p = RecordPtr;
	CDRESOURCE	cdResource;

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	if (SIG_CD_HREF == RecordType) {
	} else if (SIG_CD_HREF2 == RecordType) {
	} else if (SIG_CD_HREFBORDER == RecordType) {
	} else if (SIG_CD_TABLECELL_HREF == RecordType) {
	} else if (SIG_CD_TABLECELL_HREF2 == RecordType) {
	} else {
		scan_engine->WriteLog("Unknown resource type. RecordType=" + RecordType + 
						" (" + String::Format("{0,10:X}", RecordType) + "). NoteID=" + 
						scan_engine->scanner->SearchQuery->NoteID + ". Item=" + 
						scan_engine->scanner->SearchQuery->FieldName);
		return;
	}

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDRESOURCE, &cdResource, 1 );

	if (cdResource.ServerHintLength > 0 ) {
		// SERVER-HINT
		PrintText((char far *) p, (WORD)cdResource.ServerHintLength, ptr, "CD::Resource::Server Hint" );
		p = ((char far *) p) + cdResource.ServerHintLength;
	}
	if (cdResource.FileHintLength > 0 ) {
		// FILE-HINT
		PrintText((char far *) p, (WORD)cdResource.FileHintLength, ptr, "CD::Resource::File Hint" );
		p = ((char far *) p) + cdResource.FileHintLength;
	}

	switch( cdResource.Type ) {
	
		case CDRESOURCE_TYPE_URL:
			if( cdResource.Length1 > 0 ) {
				// URL
				if( cdResource.Flags & CDRESOURCE_FLAGS_FORMULA )
					PrintFormula( p, cdResource.Length1, ptr, "CD::Resource::URL::Formula" );
				else
					PrintText((char far *)p, (WORD)cdResource.Length1, ptr, "CD::Resource::URL::Text");
				p = ((char far *) p) + cdResource.Length1;
			}
			break;

		case CDRESOURCE_TYPE_NOTELINK: {
			if( cdResource.Flags & CDRESOURCE_FLAGS_NOTELINKINLINE ) {
				NOTELINK rscLink;
				// NOTELINK-INLINE				
				NSFAnalyzerEngine::pODSReadMemory( &p, _NOTELINK, &rscLink, 1 );
				PrintNOTELINK( &rscLink, ptr );
			}
			else
			{
				WORD rscLinkWord;
				// LINK-ID
				NSFAnalyzerEngine::pODSReadMemory( &p, _WORD, &rscLinkWord, 1 );
				scan_engine->WriteLog("Link ID: " + String::Format("{0,10:X}", rscLinkWord) );
			}
			// ANCHOR
			PrintText((char far *)p, (WORD)cdResource.Length1, ptr, "CD::Resource::Anchor");
		}
		break;
		
	case CDRESOURCE_TYPE_NAMEDELEMENT: {
			if( cdResource.Flags & CDRESOURCE_FLAGS_FORMULA )
				PrintFormula( p, cdResource.Length1, ptr, "CD::Resource::Named Element::Formula" );
			else
				PrintText((char far *)p, (WORD)cdResource.Length1, ptr, "CD::Resource::Named Element::Text" );
			p = ((char far *) p) + cdResource.Length1;
		}
		break;

	case CDRESOURCE_TYPE_ACTION: {
			if( cdResource.Flags & CDRESOURCE_FLAGS_FORMULA )
				PrintFormula( p, cdResource.Length1, ptr, "CD::Resource::Action::Formula" );
		}
		break;
		
	case CDRESOURCE_TYPE_NOTEIDLINK:
	case CDRESOURCE_TYPE_NAMEDITEMELEMENT:
	default:
		break;
	}
	return;
}

/************************************************************************

    FUNCTION:   DumpCDEvent

*************************************************************************/
void LNPUBLIC DumpCDEvent(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
	char far *	p = RecordPtr;
	CDEVENT		cdEvent;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDEVENT, &cdEvent, 1 );

	if( cdEvent.ActionLength > 0 ) {
		switch( cdEvent.ActionType ) {
			case ACTION_TYPE_FORMULA:
				PrintFormula( p, (WORD) cdEvent.ActionLength, ptr, "CD::Event::Action::Formula");
				break;
			case ACTION_TYPE_CANNED_ACTION:
				NSFDDUMPDumpMemory( p, (WORD) cdEvent.ActionLength, ptr, "CD::Event::Action::Canned Action" );
				break;
			case ACTION_TYPE_LOTUS_SCRIPT:
				PrintScriptSource( p, (WORD) cdEvent.ActionLength, ptr, "CD::Event::Action::LotusScript");
				break;
			case ACTION_TYPE_JAVASCRIPT:
				PrintText( p, (WORD) cdEvent.ActionLength, ptr, "CD::Event::Action::JavaScript" );
				break;
			default:
				NSFDDUMPDumpMemory( p, (WORD) cdEvent.ActionLength, ptr, "CD::Event::Action::Unknown" );
				break;
		}
		p = ((char far *) p) + cdEvent.ActionLength;
	}

	return;
}


/************************************************************************

    FUNCTION:   DumpCDIDName

*************************************************************************/
void LNPUBLIC DumpCDIDName(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
	char far *	p = RecordPtr;
	CDIDNAME	cdIDName;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDIDNAME, &cdIDName, 1 );

	if( cdIDName.Length > 0 ) {		
		PrintText( (char far *) p, (WORD)cdIDName.Length, ptr, "CD::ID Name" );
		p = ((char far *) p) + cdIDName.Length;
	}
	
	if( cdIDName.wClassLen > 0 ) {		
		PrintText( (char far *) p, (WORD)cdIDName.wClassLen, ptr, "CD::ID Name::Class" );
		p = ((char far *) p) + cdIDName.wClassLen;
	}
	
	if( cdIDName.wStyleLen > 0 ) {
		PrintText( (char far *) p, (WORD)cdIDName.wStyleLen, ptr, "CD::ID Name::Style" );
		p = ((char far *) p) + cdIDName.wStyleLen;
	}
	
	if( cdIDName.wTitleLen > 0 ) {		
		PrintText( (char far *) p, (WORD)cdIDName.wTitleLen, ptr, "CD::ID Name::Title" );
		p = ((char far *) p) + cdIDName.wTitleLen;
	}
	
	if( cdIDName.wExtraLen > 0 ) {		
		PrintText( (char far *) p, (WORD)cdIDName.wExtraLen, ptr, "CD::ID Name::Extra" );
		p = ((char far *) p) + cdIDName.wExtraLen;
	}
	
	if( cdIDName.wNameLen > 0 )	{		
		PrintText( (char far *) p, (WORD)cdIDName.wNameLen, ptr, "CD::ID Name::Name");
	}
	
	return;
}

/************************************************************************

    FUNCTION:   DumpCDPreTableBegin

*************************************************************************/
void LNPUBLIC DumpCDPreTableBegin(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *		p = RecordPtr;
	CDPRETABLEBEGIN	cdPreTableBegin;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDPRETABLEBEGIN, &cdPreTableBegin, 1 );
		
	if( cdPreTableBegin.NameLength > 0 ) {
		PrintText( (char far *) p, (WORD)cdPreTableBegin.NameLength, ptr, "CD::Table::Pre::Name" );
		p = ((char far *) p) + cdPreTableBegin.NameLength;
	}
	
	if( cdPreTableBegin.ImagePacketLength > 0 )	{		
		PrintText( (char far *) p, (WORD)cdPreTableBegin.ImagePacketLength, ptr, "CD::Table::Pre::Image Packet" );
		p = ((char far *) p) + cdPreTableBegin.ImagePacketLength;
	}
	
	if (cdPreTableBegin.RowLabelDataLength > 0 ) {		
		PrintText( (char far *) p, (WORD)cdPreTableBegin.RowLabelDataLength, ptr, "CD::Table::Pre::Row Label Data" );
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedSchedCtl

*************************************************************************/

void LNPUBLIC DumpCDEmbeddedSchedCtl(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *			p = RecordPtr;
	CDEMBEDDEDSCHEDCTL	cdEmbeddedSchedCtl;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDEMBEDDEDSCHEDCTL, &cdEmbeddedSchedCtl, 1 );

	if( cdEmbeddedSchedCtl.TargetFrameLength > 0 ) {	
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtl.TargetFrameLength, ptr, "CD::CDEMBEDDEDSCHEDCTL::Target Frame" );
		p = ((char far *) p) + cdEmbeddedSchedCtl.TargetFrameLength;
	}
	
	if( cdEmbeddedSchedCtl.DisplayStartDTItemFormulaLength > 0 ) {		
		PrintFormula( p, cdEmbeddedSchedCtl.DisplayStartDTItemFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTL::Display Start Date/Time Item Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtl.DisplayStartDTItemFormulaLength;
	}
	
	if( cdEmbeddedSchedCtl.HrsPerDayItemFormulaLength > 0 ) {		
		PrintFormula( p, cdEmbeddedSchedCtl.HrsPerDayItemFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTL::Hours Per Day Item Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtl.HrsPerDayItemFormulaLength;
	}

	if( cdEmbeddedSchedCtl.ReqPeopleItemsFormulaLength > 0 ) {		
		PrintFormula( p, cdEmbeddedSchedCtl.ReqPeopleItemsFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTL::Required People Items Formula" );
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDBlobPart

*************************************************************************/
void LNPUBLIC DumpCDBlobPart(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *ptr) {
	char far *	p = RecordPtr;
	CDBLOBPART	cdBlobPart;

	NSFAnalyzerEngine::pODSReadMemory(&p, _CDBLOBPART, &cdBlobPart, 1);
	
	if (cdBlobPart.Length > 0) {
		PrintText( p, (WORD) cdBlobPart.Length, ptr, "CD::Blob Part" );
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDCaption

*************************************************************************/
void LNPUBLIC DumpCDCaption(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *	p = RecordPtr;
	CDCAPTION	cdCaption;
	DWORD		dwLen;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDCAPTION, &cdCaption, 1);

	dwLen = RecordLength - (DWORD)NSFAnalyzerEngine::pODSLength(_CDCAPTION);

	if( dwLen > 0 ) {
		// Print the caption data
		PrintText( p, dwLen, ptr, "CD::Caption" );
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDFrame

*************************************************************************/
void LNPUBLIC DumpCDFrame(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *	p = RecordPtr;
	CDFRAME		cdFrame;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDFRAME, &cdFrame, 1 );

	if (cdFrame.FrameNameLength > 0) {		
		PrintText(( char far *)p, (WORD)cdFrame.FrameNameLength, ptr, "CD::Frame::Name" );
		p = ((char far *) p) + cdFrame.FrameNameLength;
	}

	if (cdFrame.FrameTargetLength > 0) {		
		PrintText(( char far *)p, (WORD)cdFrame.FrameTargetLength, ptr, "CD::Frame::Target");
		p = ((char far *) p) + cdFrame.FrameTargetLength;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDActionExt

*************************************************************************/
void LNPUBLIC DumpCDActionExt(char *RecordPtr, DWORD RecordLength, void *ptr ) {
    char far *          p = RecordPtr;
    CDACTIONEXT         cdActionExt;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONEXT, &cdActionExt, 1);

	if( cdActionExt.wControlFormulaLen > 0 ) {					/* variable data */
		PrintFormula ( p, cdActionExt.wControlFormulaLen, ptr,"CD::Action Extended::Control Formula" );	
		p = ((char far *) p) + cdActionExt.wControlFormulaLen;
	}	

	if( cdActionExt.wLabelFormulaLen > 0 ) {					/* variable data */
		PrintFormula ( p, cdActionExt.wLabelFormulaLen, ptr, "CD::Action Extended::Label Formula" );	
		p = ((char far *) p) + cdActionExt.wLabelFormulaLen;
	}	

	if( cdActionExt.wParentLabelFormulaLen > 0 ) {              /* variable data */			
		PrintFormula ( p, cdActionExt.wParentLabelFormulaLen, ptr, "CD::Action Extended::Parent Label Formula" );
		p = ((char far *) p) + cdActionExt.wParentLabelFormulaLen;
	}	

    return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedSchedCtlExtra

*************************************************************************/
void LNPUBLIC DumpCDEmbeddedSchedCtlExtra(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *				p = RecordPtr;
	CDEMBEDDEDSCHEDCTLEXTRA	cdEmbeddedSchedCtlExtra;
		
	NSFAnalyzerEngine::pODSReadMemory( &p, _CDEMBEDDEDSCHEDCTLEXTRA, &cdEmbeddedSchedCtlExtra, 1 );
	
	if( cdEmbeddedSchedCtlExtra.OptPeopleItemsFormulaLength > 0 ) {
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.OptPeopleItemsFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Optional People Items Formula");
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.OptPeopleItemsFormulaLength;
	}

	if( cdEmbeddedSchedCtlExtra.ReqRoomsItemsFormulaLength > 0 ) {	
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.ReqRoomsItemsFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Required Rooms Items Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.ReqRoomsItemsFormulaLength;
	}
	
	if( cdEmbeddedSchedCtlExtra.OptRoomsItemsFormulaLength > 0 ) {	
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.OptRoomsItemsFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Optional Rooms Items Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.OptRoomsItemsFormulaLength;
	}
	
	if( cdEmbeddedSchedCtlExtra.ReqResourcesItemsFormulaLength > 0 ) {	
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.ReqResourcesItemsFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Required Resources Items Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.ReqResourcesItemsFormulaLength;
	}

	if( cdEmbeddedSchedCtlExtra.OptResourcesItemsFormulaLength > 0 ) {		
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.OptResourcesItemsFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Optional Resources Items Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.OptResourcesItemsFormulaLength;
	}

	if( cdEmbeddedSchedCtlExtra.IntervalStartDTItemFormulaLength > 0 ) {		
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.IntervalStartDTItemFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Interval Start Date/Time Item Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.IntervalStartDTItemFormulaLength;
	}

	if( cdEmbeddedSchedCtlExtra.IntervalEndDTItemFormulaLength > 0 ) {	
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.IntervalEndDTItemFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Interval End Date/Time Item Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.IntervalEndDTItemFormulaLength;
	}

	if( cdEmbeddedSchedCtlExtra.SchedulerNameLength > 0 ) {
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.SchedulerNameLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Scheduler Name" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.SchedulerNameLength;
	}
	
	if( cdEmbeddedSchedCtlExtra.PeopleTitleLength > 0 )	{
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.PeopleTitleLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::People Title" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.PeopleTitleLength;
	}
	
	if( cdEmbeddedSchedCtlExtra.RoomsTitleLength > 0 ) {	
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.RoomsTitleLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Rooms Title" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.RoomsTitleLength;
	}
	
	if( cdEmbeddedSchedCtlExtra.ResourcesTitleLength > 0 ) {		
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.ResourcesTitleLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Resources Title" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.ResourcesTitleLength;
	}

	if( cdEmbeddedSchedCtlExtra.IntervalChangeEventFormulaLength > 0 ) {	
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.IntervalChangeEventFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Interval Change Event Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.IntervalChangeEventFormulaLength;
	}

	if( cdEmbeddedSchedCtlExtra.SchedDetailItemsFormulaLength > 0 )	{		
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.SchedDetailItemsFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Scheduled Detail Items Formula");
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.SchedDetailItemsFormulaLength;
	}
	
	if( cdEmbeddedSchedCtlExtra.DetailDisplayFormFormulaLength > 0 ) {				
		PrintFormula((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.DetailDisplayFormFormulaLength, ptr, "CD::CDEMBEDDEDSCHEDCTLEXTRA::Detail Display Form Formula" );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.DetailDisplayFormFormulaLength;
	}

	return;

}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedCalCtl

*************************************************************************/
void LNPUBLIC DumpCDEmbeddedCalCtl(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *	        p = RecordPtr;
	CDEMBEDDEDCALCTL	cdEmbeddedCalCtl;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDEMBEDDEDCALCTL, &cdEmbeddedCalCtl, 1 );

	if( cdEmbeddedCalCtl.TargetFrameLength > 0 ) {
		PrintText((char far *)p, (WORD)cdEmbeddedCalCtl.TargetFrameLength, ptr, "CD::Embedded Calendar Control::Target Frame" );
		p = ((char far *) p) + cdEmbeddedCalCtl.TargetFrameLength;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDFileHeader

*************************************************************************/
void LNPUBLIC DumpCDFileHeader(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *		p = RecordPtr;
	CDFILEHEADER	cdFileHeader;

	NSFAnalyzerEngine::pODSReadMemory( &p, _CDFILEHEADER, &cdFileHeader, 1 );

	if( cdFileHeader.FileExtLen > 0 ) {		
		PrintText((char far *)p, (WORD)cdFileHeader.FileExtLen, ptr, "CD::File Header::File Extended");
		p = ((char far *) p) + cdFileHeader.FileExtLen;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDDECSField

*************************************************************************/
void LNPUBLIC DumpCDDECSField(char *RecordPtr, DWORD RecordLength, void *ptr) {
	char far *		p = RecordPtr;
	CDDECSFIELD		cdDECSField;
	
	NSFAnalyzerEngine::pODSReadMemory( &p, _CDDECSFIELD, &cdDECSField, 1 );

	if( cdDECSField.ExternalNameLength > 0 ) {
		PrintText((char far *)p, (WORD)cdDECSField.ExternalNameLength, ptr, "CD::DECS::External Name" );
		p = ((char far *) p) + cdDECSField.ExternalNameLength;
	}

	if( cdDECSField.MetadataNameLength > 0 ) {		
		PrintText((char far *)p, (WORD)cdDECSField.MetadataNameLength, ptr, "CD::DECS::Metadata Name");
		p = ((char far *) p) + cdDECSField.MetadataNameLength;
	}

	if( cdDECSField.DCRNameLength > 0 ) {		
		PrintText((char far *)p, (WORD)cdDECSField.DCRNameLength, ptr, "CD::DECS::DCR Name" );
		p = ((char far *) p) + cdDECSField.DCRNameLength;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedEditCtl

*************************************************************************/
void LNPUBLIC DumpCDEmbeddedEditCtl(char *RecordPtr, DWORD RecordLength, void *ptr) {

	char far *			p = RecordPtr;
	CDEMBEDDEDEDITCTL	cdEmbeddedEditCtl;
	
	NSFAnalyzerEngine::pODSReadMemory( &p, _CDEMBEDDEDEDITCTL, &cdEmbeddedEditCtl, 1 );

	if( cdEmbeddedEditCtl.NameLength > 0 ) {		
		PrintText((char far *)p, (WORD)cdEmbeddedEditCtl.NameLength, ptr, "CD::Embedded Edit Control::Name" );
		p = ((char far *) p) + cdEmbeddedEditCtl.NameLength;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDFieldHint

*************************************************************************/
void LNPUBLIC DumpCDFieldHint(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *      p = RecordPtr;
    CDFIELDHINT		cdFieldHint;
    
	NSFAnalyzerEngine::pODSReadMemory( &p, _CDFIELDHINT, &cdFieldHint, 1 );

	if (0 != cdFieldHint.HintTextLength) {
		PrintText( (char far *)p, cdFieldHint.HintTextLength, ptr, "CD::Field Hint");
		p = ((char far *) p) + cdFieldHint.HintTextLength;
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbedExtraInfo
	
*************************************************************************/
void LNPUBLIC DumpCDEmbedExtraInfo(char *RecordPtr,	DWORD RecordLength, void *ptr) {
    char far *      	p = RecordPtr;
    CDEMBEDEXTRAINFO	cdEmbedExtraInfo;
    
	NSFAnalyzerEngine::pODSReadMemory( &p, _CDEMBEDEXTRAINFO, &cdEmbedExtraInfo, 1 );  
	
	if( cdEmbedExtraInfo.NameLength > 0 ){		
		PrintText( (char far *)p, (WORD)cdEmbedExtraInfo.NameLength, ptr, "CD::Embedded Extra Info::Name");
		p += cdEmbedExtraInfo.NameLength;
	}

   return;
}